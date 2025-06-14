/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:43:24 by hes-saou          #+#    #+#             */
/*   Updated: 2025/06/14 01:26:53 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../parsing/parsing.h"

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
void	print_tok(t_tok *tok);

/* execution */
void				execute_executable(t_tok *tok, char **env);
void				execute_external_cmd(t_tok *tok, char **env, int fd);
void				execute_built_in(t_tok *tok, t_shell *shell, char **env);
void				execute_cmd(t_tok *tok, char **env, int fd, t_shell *shell);

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

/* execute built-in */
void				execute_cd(t_tok *tok, t_shell *shell);
void				execute_pwd(t_shell *shell);
void				execute_echo(t_tok *tok);
void				execute_env(char **env);
void				execute_exit(t_tok *tok, t_shell *shell);
void				execute_unset(t_tok *tok, t_shell *shell);
void				execute_export(t_tok *tok, t_shell *shell);

#endif