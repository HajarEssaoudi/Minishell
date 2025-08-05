NAME        = parsing.a
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -g

SRC_DIR     = .
LEXER_DIR   = $(SRC_DIR)/lexer
WORD_DIR    = $(LEXER_DIR)/word
OPER_DIR    = $(LEXER_DIR)/operators
TOKEN_DIR   = $(SRC_DIR)/token
LIB_DIR     = ../lib

LIBFT       = $(LIB_DIR)/libft.a

SRC         = \
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
              $(TOKEN_DIR)/utils_tok.c \

OBJ         = $(SRC:.c=.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIB_DIR)

$(NAME): $(OBJ) $(LIBFT)
	cp $(LIBFT) $(NAME)
	ar rcs $(NAME) $(OBJ)

%.o: %.c parsing.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

.SECONDARY: $(OBJ)