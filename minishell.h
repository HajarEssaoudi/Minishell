#ifndef MINISHELL_H
# define MINISHELL_H

# include "lib/libft.h"
# include <ctype.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>

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
	struct s_tok	*next;
}					t_tok;

typedef struct s_div
{
	char			*args;
	char			*type;
	struct s_div	*next;
}					t_div;

typedef struct s_quot
{
	int				start;
	int				i;
	char			*str;
	char			*sub;
}					t_quot;

int					check_redirect(char *input);
int					check_pip(char *input);
char				*get_env_var(char **cp_env, char *key);
char				*check_quot(char *input, int *index, char quot,
						char **cp_env);
char				*ft_var(char *str, char **cp_env);
int					check_redirect2(char *input);
void				ft_typ(t_div *div);
t_tok				*ft_token(t_div *div);
char				**cop_env(char **env);
t_div				*ft_div(char *input, char **cp_env);
t_tok				*check_cmd(t_tok *tok, char **cp_env);

//execution
void	execute_cmd(t_tok *tok, char **env);
#endif
