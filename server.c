#include "minitalk.h"

static void	put_pid(pid_t pid, bool is_server)
{
	if (is_server == true)
	{
		ft_putstr_fd(CLR_BLACK_YELLOW, STDOUT_FILENO);
		ft_putstr_fd("PID: ", STDOUT_FILENO);
	}
	else
	{
		ft_putstr_fd(CLR_YELLOW, STDOUT_FILENO);
		ft_putstr_fd("Client PID: ", STDOUT_FILENO);
	}
	ft_putnbr_fd(pid, STDOUT_FILENO);
	ft_putstr_fd(CLR_RESET, STDOUT_FILENO);
	write(STDOUT_FILENO, "\n", 1);
}

static void	signal_handler(int signo, siginfo_t *info, void *context)
{
	static unsigned char	c = 0;
	static int				i = BIT_PER_CHAR;
	static pid_t			pid = 0;

	(void)context;
	c |= ((signo == SIGUSR1) << --i);
	if (pid != info->si_pid)
	{
		pid = info->si_pid;
		put_pid(pid, false);
	}
	if (i == 0)
	{
		i = BIT_PER_CHAR;
		if (c == '\0')
		{
			write(STDOUT_FILENO, "\n", 1);
			kill(pid, SIGUSR2);
			return ;
		}
		write(STDOUT_FILENO, &c, 1);
		c = 0;
	}
	kill(pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	act;

	put_pid(getpid(), true);
	act.sa_sigaction = signal_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &act, NULL) < 0
		|| sigaction(SIGUSR2, &act, NULL) < 0)
	{
		ft_putendl_fd(MSG_SIGACT_FAILED, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	while (1)
		pause();
	exit(EXIT_SUCCESS);
}
