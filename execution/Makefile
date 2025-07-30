NAME = libexecution.a
CC = cc
CFLAGS = -g3 -fPIE
# CFLAGS += -Wall -Wextra -Werror 

SRCS =	helpers.c env_helpers.c execution.c execute_execve.c execute_builtin.c pipe_executor.c \
		redirections/execute_redirections.c redirections/operations.c \
		built-in/builtin_helpers.c built-in/execute_cd.c built-in/execute_echo.c \
		built-in/execute_env.c built-in/execute_exit.c built-in/execute_export.c \
		built-in/execute_pwd.c built-in/execute_unset.c \
		free.c signal.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SECONDARY: $(OBJS)
