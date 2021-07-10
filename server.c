#include "minitalk.h"

static void	put_pid(void)
{
	ft_putstr_fd("PID: ", STDOUT_FILENO);
	ft_putnbr_fd(getpid(), STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

static void	signal_handler(int signo, siginfo_t *info, void *context)
{
	static unsigned char	c = 0;
	static int				i = 7;

	(void)context;
	c |= ((signo == SIGUSR1) << i);
	if (--i == -1)
	{
		i = 7;
		if (c == '\0')
		{
			write(STDOUT_FILENO, "\n", 1);
			kill(info->si_pid, SIGUSR2);
			return ;
		}
		write(STDOUT_FILENO, &c, 1);
		c = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	act;

	put_pid();
	// act.sa_handler ではなくて良いのか -> infoをとるためにsa_sigaction
	act.sa_sigaction = signal_handler;
	// シグナルマスク(ブロックするシグナルの集合)を初期化(全てのシグナルを除外)
	sigemptyset(&act.sa_mask);
	// sa_flagsにSA_SIGINFOを指定しsignalに関する詳細な情報siginfo_tを受け取る
	act.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &act, NULL) < 0)
		return (EXIT_FAILURE);
	if (sigaction(SIGUSR2, &act, NULL) < 0)
		return (EXIT_FAILURE);
	while (1)
		pause();
	exit(EXIT_SUCCESS);
}
