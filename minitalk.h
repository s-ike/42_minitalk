#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdbool.h>
# include "libft/libft.h"

# define CLIENT_USLEEP 20
# define MSG_EINVAL "Invalid argument"
# define MSG_FAILED "kill failed"

# define CLR_BLACK_YELLOW "\033[30;43m"
# define CLR_RED "\033[31m"
# define CLR_GREEN "\033[32m"
# define CLR_YELLOW "\033[33m"
# define CLR_RESET "\033[0m"

uint64_t	g_client_strlen;

#endif
