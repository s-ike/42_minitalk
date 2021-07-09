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
	if (ft_strlen(argv[2]) == 0)
		return (false);
	return (true);
}

static void	send_char(int pid, unsigned char c)
{
	int	i;

	i = 7;
	while (0 <= i)
	{
		if (c & (1 << i))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i--;
		usleep(CLIENT_USLEEP);
	}
}

static void	send_str(int pid, const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		send_char(pid, s[i]);
		i++;
		if (s[i] == '\0')
			send_char(pid, s[i]);
	}
}
#include <stdio.h>
int	main(int argc, char **argv)
{
	// int	argc = 3;
	// char	*argv[] = {"./client", "66291", "a", NULL};

	if (!validate_args(argc, argv))
	{
		ft_putendl_fd("Invalid argument", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	send_str(ft_atoi(argv[1]), argv[2]);
	exit(EXIT_SUCCESS);
}
