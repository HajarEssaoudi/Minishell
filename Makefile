NAME        = minishell
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -g

SRC_DIR     = parsing
LIB_DIR     = lib
PRINTF_DIR  = ft_printf
EXECUTION_DIR = execution

LIBFT       = $(LIB_DIR)/libft.a
PRINTF_LIB  = $(PRINTF_DIR)/libftprintf.a
EXECUTION_LIB = $(EXECUTION_DIR)/libexecution.a
PARSING_LIB = $(SRC_DIR)/parsing.a

MAIN_SRC    = main.c

MAIN_OBJ    = $(MAIN_SRC:.c=.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIB_DIR)

$(PRINTF_LIB):
	$(MAKE) -C $(PRINTF_DIR)

$(EXECUTION_LIB):
	$(MAKE) -C $(EXECUTION_DIR)

$(PARSING_LIB): $(LIBFT)
	$(MAKE) -C $(SRC_DIR)

$(NAME): $(MAIN_OBJ) $(PARSING_LIB) $(PRINTF_LIB) $(EXECUTION_LIB)
	$(CC) $(CFLAGS) -o $@ $(MAIN_OBJ) $(PARSING_LIB) $(PRINTF_LIB) $(EXECUTION_LIB) -lreadline -lncurses

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(MAIN_OBJ)
	$(MAKE) -C $(LIB_DIR) clean
	$(MAKE) -C $(PRINTF_DIR) clean
	$(MAKE) -C $(EXECUTION_DIR) clean
	$(MAKE) -C $(SRC_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean
	$(MAKE) -C $(PRINTF_DIR) fclean
	$(MAKE) -C $(EXECUTION_DIR) fclean
	$(MAKE) -C $(SRC_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

.SECONDARY: $(MAIN_OBJ)
