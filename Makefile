# **************************************************************************** #
#                                  Makefile                                   #
# **************************************************************************** #

NAME        = minishell
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -g

# Répertoires
SRC_DIR     = parsing
LEXER_DIR   = $(SRC_DIR)/lexer
WORD_DIR    = $(LEXER_DIR)/word
OPER_DIR    = $(LEXER_DIR)/operators
TOKEN_DIR   = $(SRC_DIR)/token
PRINTF_DIR  = ft_printf
LIB_DIR     = lib
EXECUTION_DIR = execution

# Fichiers sources
SRC         = \
              $(SRC_DIR)/main.c \
              $(SRC_DIR)/cmd.c \
              $(SRC_DIR)/cmd_utils.c \
              $(SRC_DIR)/copie_env.c \
              $(SRC_DIR)/ft_free.c \
              $(LEXER_DIR)/lexer.c \
              $(LEXER_DIR)/ft_utils.c \
              $(WORD_DIR)/expand.c \
              $(WORD_DIR)/ft_split_final.c \
              $(WORD_DIR)/get_variable.c \
              $(WORD_DIR)/ft_utils_word.c \
              $(WORD_DIR)/fin_lexer.c \
              $(WORD_DIR)/final.spaces.c \
              $(WORD_DIR)/get_str.c \
              $(WORD_DIR)/handl_word.c \
              $(WORD_DIR)/split_str.c \
              $(OPER_DIR)/handle_operator.c \
              $(OPER_DIR)/pip.c \
              $(OPER_DIR)/redirect.c \
              $(OPER_DIR)/redirect2.c \
              $(TOKEN_DIR)/ft_get_type.c \
              $(TOKEN_DIR)/ft_token.c \
              $(TOKEN_DIR)/general_tok.c \
              $(TOKEN_DIR)/utils_tok.c

# Ajout ft_printf et lib
SRC         += $(wildcard $(PRINTF_DIR)/*.c)
SRC         += $(wildcard $(LIB_DIR)/*.c)

# Objets
OBJ         = $(SRC:.c=.o)

# Chemin vers la bibliothèque execution
EXECUTION_LIB = $(EXECUTION_DIR)/libexecution.a

# Compilation
all: $(EXECUTION_LIB) $(NAME)

$(EXECUTION_LIB):
	$(MAKE) -C $(EXECUTION_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(EXECUTION_LIB) -lreadline -lncurses

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(EXECUTION_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(EXECUTION_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
