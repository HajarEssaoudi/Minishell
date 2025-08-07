NAME        = libexecution.a
CC          = cc
CFLAGS      = -Wall -Wextra -Werror

SRC         = \
			  cmd.c cmd_utils.c helpers.c env_helpers.c \
			  redirections/redirectios_helpers.c \
			  execute_execve_helpers.c pipe_executor_helpers.c execution.c \
			  execute_execve.c execute_builtin.c pipe_executor.c \
			  redirections/execute_redirections.c redirections/operations.c \
			  redirections/herdoc_expansion.c redirections/ft_herdoc.c \
			  redirections/herdoc_helpers.c built-in/builtin_helpers.c \
			  built-in/execute_cd.c built-in/execute_echo.c \
			  built-in/execute_env.c built-in/execute_exit.c \
			  built-in/execute_export.c built-in/execute_pwd.c \
			  built-in/execute_unset.c free.c signal.c

OBJ         = $(SRC:.c=.o)

LIBFT       = ../libft/libft.a
PRINTF      = ../ft_printf/libftprintf.a

INCLUDES    = -I../includes -I../libft -I../ft_printf

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all