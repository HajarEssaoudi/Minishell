NAME = libftprintf.a
CC  = gcc
CFLAGS = -Werror -Wextra -Wall
SRC = ft_printf.c utils.c utils_extra.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re