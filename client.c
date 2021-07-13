#include "minitalk.h"

static int	is_pid_format(const char *s)
{
	if (!s || *s == '\0')
		return (false);
	if (!ft_isdigit(*s))
		return (false);
	if (*s == '0')
		return (false);
	s++;
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (false);
		s++;
	}
	return (true);
}

static int	validate_args(int argc, char **argv)
{
	if (argc != 3)
		return (false);
	if (!is_pid_format(argv[1]))
		return (false);
	g_client_strlen = ft_strlen(argv[2]);
	if (g_client_strlen == 0)
		return (false);
	return (true);
}

static int	send_str(pid_t pid, const char *s)
{
	const int		signals[] = {SIGUSR2, SIGUSR1};
	static char		*save_s;
	static pid_t	save_p = 0;
	static int		i = 7;

	if (s)
	{
		save_s = (char *)s;
		save_p = pid;
	}
	if (0 <= i)
	{
		usleep(CLIENT_USLEEP);
		if (kill(save_p, signals[!!(*save_s & (1 << i--))]) == -1)
			return (false);
	}
	if (i < 0)
	{
		if (*save_s == '\0')
			return (true);
		i = 7;
		save_s++;
	}
	return (true);
}

static void	signal_handler(int signo)
{
	static uint64_t	cnt = 0;

	if (signo == SIGUSR1 || signo == SIGUSR2)
	{
		ft_putstr_fd("\rACK: ", STDOUT_FILENO);
		ft_putnbr_fd(++cnt, STDOUT_FILENO);
	}
	if (signo == SIGUSR1)
		send_str(0, NULL);
	if (signo == SIGUSR2)
	{
		write(STDOUT_FILENO, "\n", 1);
		if ((g_client_strlen + 1ULL) * 8ULL == cnt)
		{
			ft_putstr_fd(CLR_GREEN, STDOUT_FILENO);
			ft_putendl_fd("SUCCESS", STDOUT_FILENO);
		}
		else
		{
			ft_putstr_fd(CLR_RED, STDOUT_FILENO);
			ft_putendl_fd("FAILED", STDOUT_FILENO);
		}
		ft_putstr_fd(CLR_RESET, STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	act;

	act.sa_handler = signal_handler;
	sigemptyset(&act.sa_mask);
	if (sigaction(SIGUSR1, &act, NULL) < 0
		|| sigaction(SIGUSR2, &act, NULL) < 0)
	{
		ft_putendl_fd(MSG_SIGACT_FAILED, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (!validate_args(argc, argv))
	{
		ft_putendl_fd(MSG_EINVAL, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (send_str(ft_atoi(argv[1]), argv[2]) == false)
	{
		ft_putendl_fd(MSG_KILL_FAILED, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	while (1)
		pause();
	exit(EXIT_FAILURE);
}
