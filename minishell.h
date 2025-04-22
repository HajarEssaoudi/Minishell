#ifndef MINISHELL_H
# define MINISHELL_H

# include "lib/libft.h"
# include <ctype.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_tok
{
	char			**str;
	char			*path;
	char			*heredoc;
	char			*output;
	char			*input;
	char			*append;
	char			*pip;
	char			*filename;
	struct s_tock	*next;
}					t_tok;

typedef struct s_div
{
	char			*args;
	char			*type;
	struct s_div	*next;
}					t_div;

int					check_redirect(char *input);
int					check_pip(char *input);
char				*get_env_var(char **cp_env, char *key);
char				*check_quot(char *input, int *index, char quot,
						char **cp_env);
char				*ft_var(char *str, char **cp_env);
int					check_redirect2(char *input);
void				ft_typ(t_div *div);
#endif
