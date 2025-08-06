NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Wextra -Werror

EXEC_DIR    = execution
PARSING_DIR = parsing
LIB_DIR     = lib
PRINTF_DIR  = ft_printf

EXEC_LIB    = $(EXEC_DIR)/libexecution.a
PARSING_LIB = $(PARSING_DIR)/libparsing.a
LIBFT       = $(LIB_DIR)/libft.a
PRINTF      = $(PRINTF_DIR)/libftprintf.a

INCLUDES    = -Iincludes -I$(LIB_DIR) -I$(PRINTF_DIR)
LIBS        = $(EXEC_LIB) $(PARSING_LIB) $(LIBFT) $(PRINTF)
SRC         = main.c
OBJ         = $(SRC:.c=.o)

all: $(NAME)

$(EXEC_LIB):
	$(MAKE) -C $(EXEC_DIR)

$(PARSING_LIB):
	$(MAKE) -C $(PARSING_DIR)

$(LIBFT):
	$(MAKE) -C $(LIB_DIR)

$(PRINTF):
	$(MAKE) -C $(PRINTF_DIR)

$(NAME): $(OBJ) $(EXEC_LIB) $(PARSING_LIB) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBS) -lreadline -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) clean -C $(EXEC_DIR)
	$(MAKE) clean -C $(PARSING_DIR)
	$(MAKE) clean -C $(LIB_DIR)
	$(MAKE) clean -C $(PRINTF_DIR)
	rm -f $(OBJ)

fclean: clean
	$(MAKE) fclean -C $(EXEC_DIR)
	$(MAKE) fclean -C $(PARSING_DIR)
	$(MAKE) fclean -C $(LIB_DIR)
	$(MAKE) fclean -C $(PRINTF_DIR)
	rm -f $(NAME)

re: fclean all