NAME		:= minitalk

SERVER_NAME	:= server
SERVER_SRCS	:= server.c utils.c
SERVER_OBJS	:= $(SERVER_SRCS:.c=.o)

CLIENT_NAME	:= client
CLIENT_SRCS	:= client.c utils.c
CLIENT_OBJS	:= $(CLIENT_SRCS:.c=.o)

CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror
DEBUG		:=

RM			:= rm -f
C_GREEN		:= "\x1b[32m"
C_DEFAULT	:= "\x1b[39m"
C_RESET		:= "\x1b[0m"

all:		$(NAME)

$(NAME):	$(SERVER_NAME) $(CLIENT_NAME)
			@echo $(C_GREEN)"=== Make Done ==="$(C_DEFAULT)$(C_REST)

$(SERVER_NAME):	$(SERVER_OBJS)
			$(CC) $(CFLAGS) $(DEBUG) $^ -o $@

$(CLIENT_NAME):	$(CLIENT_OBJS)
			$(CC) $(CFLAGS) $(DEBUG) $^ -o $@

clean:
			$(RM) $(SERVER_OBJS) $(CLIENT_OBJS)

fclean:		clean
			$(RM) $(SERVER_NAME) $(CLIENT_NAME)

re:			fclean $(NAME)

bonus:		$(NAME)

.PHONY:		all clean fclean re bonus
