#ifndef MINISHELL_H
# define MINISHELL_H

# include "lib/libft.h"
# include <ctype.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>

typedef struct s_tok
{
	char			**str;
	char			*execute;
	char			*path;
	char			**heredoc;
	char			**output;
	char			**input;
	char			**append;
	char			*pip;
	// char			*filename;
	char			**env;
	char			*pwd;
	char			*old_pwd;
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

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_shell
{
	char			*old_path;
	char			*current_path;
	unsigned char	exit_status;
	struct s_env	env;
}					t_shell;

t_div				*handle_pip(char *input, int *i, t_div *div);
t_div				*ft_operator(char *input, int *i, t_div *div);
void				add_ch(t_div **div, char *type, char *input);
int					check_redirect1(char *input);
int					check_pip(char *input);
char				*get_env_var(char **cp_env, char *key);
char				*check_quot(char *input, int *index, char quot,
						char **cp_env);
char				*ft_str(char *input, int *i, char **cp_env);
char				*ft_var(char *str, char **cp_env, char input);
int					check_redirect2(char *input);
void				ft_type(t_div *div);
t_tok				*ft_token(t_div *div);
char				**copy_env(char **env);
t_div				*ft_div(char *input, char **cp_env);
void				free_div(t_div *div);
t_tok				*check_cmd(t_tok *tok, char **cp_env);
char				*is_built_in(char *input, char **cp_env);
void				ft_out(t_tok *tok, char **cp_env, t_shell *shell);
void				free_tok(t_tok *tok);
void				ft_hand(int sig);
void				free_str(char **str);

// execution

/*handle env*/
t_env				*create_list_env(char **arr_env);
t_env				*init_lst_env(t_env *env, char **arr_env);

char				*get_path(void);

void				execute_executable(t_tok *tok, char **env);
void				execute_cmd(t_tok *tok, char **env, int fd, t_shell *shell);

/*execute built-in*/
void				execute_cd(t_tok *tok, t_shell *shell);
void				execute_pwd(t_tok *tok, t_shell *shell);
void				execute_echo(t_tok *tok);
void				execute_env(t_tok *tok, t_shell *shell);
void				execute_exit(t_tok *tok, t_shell *shell);
#endif
