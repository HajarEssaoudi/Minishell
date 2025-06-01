NAME = minishell
CC = cc
CFLAGS = -g3
# -Werror -Wextra -Wall

LIBFT = lib/libft.a

SRCS = 	pip.c copie_env.c handle_operator.c main.c quote.c \
		ft_free.c handl_word.c redirect2.c ft_dollar.c ft_token.c \
		ft_utils.c lexer.c redirect.c get_variable.c ft_get_type.c \

OBJS = $(SRCS:.c=.o)


do : all clean
all : $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) -lreadline -lncurses

$(LIBFT):
	make -C lib

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C lib clean
fclean: clean
	rm -f $(NAME)
	make -C lib fclean
re: fclean all

.PHONY: all clean fclean re

.SECONDARY: $(OBJS)