/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:43:24 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/06 14:16:59 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../parsing/parsing.h"

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define EXIT_NOT_FOUND 127
# define EXIT_NO_PERMISSION 126
# define TMP "/tmp/"
# define CHARACTER "abcdefghijklmnopqrstuvwxyz0123456789"
# define EXTENSION ".tmp.txt"

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
	int				exit_status;
	int				saved_stdout;
	int				saved_stdin;
	char			**arr_env;
	struct s_env	*env;
}					t_shell;

typedef struct s_redir
{
	char			*last_out;
	char			*last_in;
	char			*last_append;
}					t_redir;

typedef struct s_clean
{
	t_tok			*tok;
	char			**env;
	t_shell			*shell;
	int				fd;
	char			*name;
}					t_clean;

t_clean				*clean_heredoc(void);

/*to be deleted */
void				print_tok(t_tok *tok);

/* execution */

void				execute_cmd(t_tok *tok, t_shell *shell, char **env);
void				ft_execve(t_tok *tok, char **env);
void				execute_with_execve(t_tok *tok, t_shell *shell, char **env);
void				execute_cases(t_tok *tok, t_shell *shell, char **env);
void				execute_with_pipe(t_tok *tok, char **env, t_shell *shell);
t_tok				*check_cmd(t_tok *tok, t_shell *shell, char **cp_env);
void				tok_error_handling(t_shell *shell, char **env);

/*shell's operations*/

int					execute_redirect(t_tok *tok, t_shell *shell);
void				ft_out(char *filename, t_shell *shell);
void				ft_in(char *filename, t_shell *shell);
void				ft_herdoc(t_tok *tok, t_rederict *redir, char **env,
						t_shell *shell);
void				ft_append(char *filename, t_shell *shell);
int					out_red(t_redir *redir, char *filename, t_shell *shell);
int					in_red(t_redir *redir, char *filename, t_shell *shell);

/* helpers */
int					is_built_in(char *input);
char				*ft_strjoin_env(char const *s1, char const *s2, char sep);
int					ft_str_num(char *str);
int					ft_lst_size(t_env *lst);
int					check_ambg(t_rederict *tmp, t_shell *shell);
char				*ft_expand(char *line, char **env, int exit_status);
int					open_file(char *path, t_shell *shell);
void				fork_error(void);
char				*generate_name(void);

/* handle env */
t_env				*create_list_env(char **arr_env, t_tok *tok,
						t_shell *shell);
t_env				*init_node_env(char *str_env, t_shell *shell);
char				**update_env_arr(t_env *lst_env, char **arr_env);
void				ft_lstadd_back_env(t_env **lst, t_env *new, int f);

/* built in utils */
char				*get_path(void);
void				print_strings(char **str, int i);
void				list_env_variables(t_shell *shell);
void				print_env(t_env *env);
t_env				*add_to_env(char *str_env, t_shell *shell);

/* execute built-in */
int					execute_built_in(t_tok *tok, t_shell *shell, char **env);
int					execute_cd(t_tok *tok, t_shell *shell);
int					execute_pwd(t_shell *shell);
int					execute_echo(t_tok *tok);
int					execute_env(t_tok *tok, t_shell *shell);
int					execute_exit(t_tok *tok, t_shell *shell, char **env);
int					execute_unset(t_tok *tok, t_shell *shell);
int					execute_export(t_tok *tok, t_shell *shell);

/*freeing*/
void				free_list_env(t_env *env);
void				ft_clear(char **cp_env, t_shell *shell);

/*signal*/
void				ft_handle(int sig);
void				ft_handle_herdoc(int sig);

/*helpers*/

void				open_pipe(t_tok *tok, int *fd);
void				check_herdoc_fd(t_tok *tok);

#endif