NAME = libexecution.a
CC = cc
CFLAGS = -g3
# CFLAGS += -Wall -Wextra -Werror  # Uncomment for stricter checking

LIBFT = ../lib/libft.a
PARSING = ../parsing/libparsing.a

SRCS =	helpers.c execute_cmd.c built-in/builtin_helpers.c \
		built-in/execute_cd.c built-in/execute_echo.c built-in/execute_env.c \
		built-in/execute_exit.c built-in/execute_export.c built-in/execute_pwd.c \
		built-in/execute_unset.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re

.SECONDARY: $(OBJS)
