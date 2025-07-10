/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:43:24 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/10 01:29:12 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../parsing/parsing.h"

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define EXIT_NOT_FOUND 127
# define EXIT_NO_PERMISSION 126

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
	struct s_env	*env;
}					t_shell;

/*to be deleted */
void				print_tok(t_tok *tok);

/* execution */

void				execute_cmd(t_tok *tok, t_shell *shell, char **env);
void				ft_execve(char *path, char **str, char **env);
void				execute_with_execve(t_tok *tok, t_shell *shell, char **env);
void				execute_cases(t_tok *tok, t_shell *shell, char **env);
void				execute_with_pipe(t_tok *tok, char **env, t_shell *shell);
// void				execute_executable(t_tok *tok, char **env);

/*shell's operations*/

void				execute_redirect(t_tok *tok, char **env, t_shell *shell);
void				ft_out(t_tok *tok, char *filename, char **env,
						t_shell *shell);
void				ft_in(t_tok *tok, char *filename, char **env,
						t_shell *shell);
void				ft_herdoc(t_tok *tok, char *delimiter, char **env,
						t_shell *shell);
void				ft_append(t_tok *tok, char *filename, char **env,
						t_shell *shell);

/* helpers */
int					is_built_in(char *input, char **cp_env);
char				*ft_strjoin_env(char const *s1, char const *s2, char sep);
int					ft_str_num(char *str);

/* handle env */
t_env				*create_list_env(char **arr_env);
t_env				*init_node_env(char *str_env);
char				**update_env_arr(t_env *lst_env, char **arr_env);
void				ft_lstadd_back_env(t_env **lst, t_env *new);

/* built in utils */
char				*get_path(void);
void				print_strings(char **str, int i);
void				change_env_paths(t_shell *shell);
void				list_env_variables(t_shell *shell);
void				print_env(t_env *env);

/* execute built-in */
void				execute_built_in(t_tok *tok, t_shell *shell, char **env);
void				execute_cd(t_tok *tok, t_shell *shell);
void				execute_pwd(t_shell *shell);
void				execute_echo(t_tok *tok);
void				execute_env(char **env);
void				execute_exit(t_tok *tok, t_shell *shell);
void				execute_unset(t_tok *tok, t_shell *shell);
void				execute_export(t_tok *tok, t_shell *shell);

/*freeing*/
void				free_list_env(t_env *env);
void				ft_clear(char **cp_env, t_shell *shell, t_tok *tok);

#endif