NAME = minishell
CC = cc
CFLAGS = -g3
LIBFT = lib/libft.a
EXEC = execution/libexecution.a

SRCS = main.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(EXEC)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(EXEC) -lreadline -lncurses

$(LIBFT):
	make -C lib

$(EXEC):
	make -C execution

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C lib clean
	make -C execution clean

fclean: clean
	rm -f $(NAME)
	make -C lib fclean
	make -C execution fclean

re: fclean all

.PHONY: all clean fclean re
