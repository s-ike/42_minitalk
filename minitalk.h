#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>

# define CLIENT_USLEEP 10
# define BIT_PER_CHAR 8
# define MSG_SIGACT_FAILED "sigaction setting failed"
# define MSG_EINVAL "Invalid argument"
# define MSG_KILL_FAILED "kill failed"

# define CLR_BLACK_YELLOW "\033[30;43m"
# define CLR_RED "\033[31m"
# define CLR_GREEN "\033[32m"
# define CLR_YELLOW "\033[33m"
# define CLR_RESET "\033[0m"

uint64_t	g_client_strlen;

int		ft_atoi(const char *str);
size_t	ft_strlen(const char *s);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);

#endif
