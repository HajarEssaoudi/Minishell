NAME = minishell
CC = cc
CFLAGS = -g3
# CFLAGS = -Wall -Wextra -Werror


SRCS = main.c
OBJS = $(SRCS:.c=.o)

LIBFT_PATH = lib
PARSING_PATH = parsing
EXECUTION_PATH = execution

LIBS =	-L$(EXECUTION_PATH) -lexecution \
		-L$(PARSING_PATH) -lparsing \
		-L$(LIBFT_PATH) -lft


do: all clean

all: libparsing libft libexecution $(NAME)

libft:
	make -C $(LIBFT_PATH)

libparsing:
	make -C $(PARSING_PATH)

libexecution:
	make -C $(EXECUTION_PATH)

$(NAME): $(OBJS) libexecution libparsing libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $@ -lreadline -lncurses

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C lib clean
	make -C parsing clean
	make -C execution clean

fclean: clean
	rm -f $(NAME)
	make -C lib fclean
	make -C parsing fclean
	make -C execution fclean

re: fclean all

.PHONY: all clean fclean re
