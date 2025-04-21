#ifndef MINISHELL_H
# define MINISHELL_H

#include "lib/libft.h"
#include <ctype.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int		check_redirect(char *input);
int		check_pip(char *input);
char	*get_env_var(char **cp_env, char *key);
char *check_quot(char *input, int *index, char quot, char **cp_env);
char	*ft_var(char *str, char **cp_env);
int		check_redirect2(char *input);
#endif
