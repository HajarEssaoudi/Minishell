NAME = minishell
CC = cc
CFLAGS = 
# -Werror -Wextra -Wall

LIBFT = libft/libft.a

SRCS = main.c \

OBJS = $(SRCS:.c=.o)


do : all clean
all : $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) -lreadline

$(LIBFT):
	make -C libft

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C libft clean
fclean: clean
	rm -f $(NAME)
	make -C libft fclean
re: fclean all

.PHONY: all clean fclean re

.SECONDARY: $(OBJS)
