#include "minitalk.h"

static void	put_colored_endl_fd(char *s, char *color, int fd)
{
	ft_putstr_fd(color, fd);
	ft_putstr_fd(s, fd);
	ft_putendl_fd(CLR_RESET, fd);
}

static int	is_pid_format(const char *s)
{
	if (!s || *s == '\0')
		return (false);
	if (!('1' <= *s && *s <= '9'))
		return (false);
	s++;
	while (*s)
	{
		if (!('0' <= *s && *s <= '9'))
			return (false);
		s++;
	}
	return (true);
}

static int	send_str(pid_t pid, const char *s)
{
	const int		signals[] = {SIGUSR2, SIGUSR1};
	static char		*save_s;
	static pid_t	save_p = 0;
	static int		i = BIT_PER_CHAR;

	if (s)
	{
		save_s = (char *)s;
		save_p = pid;
	}
	if (0 < i)
	{
		usleep(CLIENT_USLEEP);
		if (kill(save_p, signals[!!(*save_s & (1 << --i))]) == -1)
			return (false);
	}
	if (i <= 0)
	{
		if (*save_s == '\0')
			return (true);
		i = BIT_PER_CHAR;
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
			put_colored_endl_fd("SUCESS", CLR_GREEN, STDOUT_FILENO);
		else
			put_colored_endl_fd("FAILED", CLR_RED, STDOUT_FILENO);
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
		put_colored_endl_fd(MSG_SIGACT_FAILED, CLR_RED, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (argc != 3 || !is_pid_format(argv[1]))
	{
		put_colored_endl_fd(MSG_EINVAL, CLR_RED, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	g_client_strlen = ft_strlen(argv[2]);
	if (send_str(ft_atoi(argv[1]), argv[2]) == false)
	{
		put_colored_endl_fd(MSG_KILL_FAILED, CLR_RED, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	while (1)
		pause();
	exit(EXIT_FAILURE);
}
