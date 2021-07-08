#include "minitalk.h"

void	put_pid(void)
{
	ft_putstr_fd("PID: ", STDOUT_FILENO);
	ft_putnbr_fd(getpid(), STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void	signal_handler(int signo, siginfo_t *info, void *context)
{
	(void)context;
	if (signo == SIGUSR1)
	{
		ft_putnbr_fd(info->si_pid, STDOUT_FILENO);
		ft_putendl_fd(" user1", STDOUT_FILENO);
	}
	else if (signo == SIGUSR2)
	{
		ft_putnbr_fd(info->si_pid, STDOUT_FILENO);
		ft_putendl_fd(" user2", STDOUT_FILENO);
	}
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
