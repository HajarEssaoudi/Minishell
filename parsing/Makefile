NAME = libparsing.a
CC = cc
CFLAGS = -g3
# CFLAGS = -Wall -Wextra -Werror

LIBFT = ../lib/libft.a

SRCS = 	pip.c copie_env.c handle_operator.c quote.c \
		ft_free.c handl_word.c redirect2.c ft_dollar.c ft_token.c \
		ft_utils.c lexer.c redirect.c get_variable.c ft_get_type.c general_tok.c \

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
