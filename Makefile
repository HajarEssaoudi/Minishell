NAME = minishell
CC = cc
CFLAGS = -g3
# CFLAGS = -Wall -Wextra -Werror

SRCS = main.c
OBJS = $(SRCS:.c=.o)

LIBFT_PATH = lib
PARSING_PATH = parsing
EXECUTION_PATH = execution
FT_PRINTF = ft_printf

LIBS =	-L$(EXECUTION_PATH) -lexecution \
		-L$(PARSING_PATH) -lparsing \
		-L$(FT_PRINTF) -lftprintf \
		-L$(LIBFT_PATH) -lft

SUBDIRS = $(LIBFT_PATH) $(PARSING_PATH) $(EXECUTION_PATH) $(FT_PRINTF)

do: all clean

all: libparsing libft libexecution libprintf $(NAME)

libft:
	make -C $(LIBFT_PATH)

libparsing:
	make -C $(PARSING_PATH)

libexecution:
	make -C $(EXECUTION_PATH)

libprintf:
	make -C $(FT_PRINTF)

$(NAME): $(OBJS) libexecution libparsing libft libprintf
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $@ -lreadline -lncurses

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	for dir in $(SUBDIRS); do make -C $$dir clean; done

fclean: clean
	rm -f $(NAME)
	for dir in $(SUBDIRS); do make -C $$dir fclean; done

re: fclean all

.PHONY: all clean fclean re
