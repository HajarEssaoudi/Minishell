NAME = minishell
CC = cc
CFLAGS = -g
# -Werror -Wextra -Wall

LIBFT = lib/libft.a

SRCS = copie_env.c get_variable.c pip.c redirect.c \
cmd.c div.c main.c quote.c redirect2.c token.c execute_cmd.c\
execute_built_in.c \

OBJS = $(SRCS:.c=.o)


do : all clean
all : $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) -lreadline

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