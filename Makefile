NAME		:= minitalk

SERVER_NAME	:= server
SERVER_SRCS	:= server.c
SERVER_OBJS	:= $(SERVER_SRCS:.c=.o)

CLIENT_NAME	:= client
CLIENT_SRCS	:= client.c
CLIENT_OBJS	:= $(CLIENT_SRCS:.c=.o)

LIBDIR		:= ./libft
LIBPATH		:= $(LIBDIR)/libft.a
LFLAGS		:= -L${LIBDIR} -lft -lcurses

CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror
DEBUG		:=

RM			:= rm -f
C_GREEN		:= "\x1b[32m"

all:		$(NAME)

$(NAME):	server client
			@echo $(C_GREEN)"=== Make Done ==="

$(LIBPATH):
			$(MAKE) -C $(LIBDIR)

server:		$(SERVER_OBJS) $(LIBPATH)
			$(CC) $(CFLAGS) $(SERVER_OBJS) $(DEBUG) $(LFLAGS) -o $(SERVER_NAME)

client:		$(CLIENT_OBJS) $(LIBPATH)
			$(CC) $(CFLAGS) $(CLIENT_OBJS) $(DEBUG) $(LFLAGS) -o $(CLIENT_NAME)

init:		## git clone --recursive https://this_repository
			git submodule update --init

clean:
			$(RM) $(SERVER_OBJS) $(CLIENT_OBJS)
			$(MAKE) clean -C $(LIBDIR)

fclean:		clean
			$(RM) $(SERVER_NAME) $(CLIENT_NAME)
			$(MAKE) fclean -C $(LIBDIR)

re:			fclean $(NAME)

.PHONY:		all clean fclean re init
