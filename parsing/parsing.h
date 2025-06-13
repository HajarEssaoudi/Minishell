/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 09:45:17 by mabdelha          #+#    #+#             */
/*   Updated: 2025/06/12 21:11:58 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../lib/libft.h"
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
	char			**env;
	char			*pwd;
	char			*old_pwd;
	struct s_tok	*next;
}					t_tok;

typedef struct s_lexer
{
	char			*args;
	char			*type;
	struct s_lexer	*next;
}					t_lexer;

typedef struct s_quot
{
	int				start;
	int				i;
	char			*str;
	char			*sub;
}					t_quot;

char				**copy_env(char **env);
void				free_str(char **str, int flag);
void				free_lexer(t_lexer *lexer);
int					skip_space_tab_newline(char *str, int i);
t_lexer				*ft_operator(char *input, int *i, t_lexer *lexer);
int					check_redirect1(char *input);
int					check_redirect2(char *input);
t_lexer				*get_str(char *input, int *i, t_lexer *lexer,
						char **cp_env);
char				*ft_str(char *input, int *i, char **cp_env);
void				add_ch(t_lexer **lexer, char *type, char *input);
char				*check_quot(char *input, int *index, char quot,
						char **cp_env);
char				*ft_var(char *str, char **cp_env, char input);
t_lexer				*handle_pip(char *input, int *i, t_lexer *div);
t_lexer				*ft_lexer(char *input, char **env);
char				*ft_dollar(char *str, char **cp_env, char *result, int *i);
char				*get_env_var(char **cp_env, char *var);
void				ft_type(t_lexer *lexer);
t_tok				*get_tok(char *prompt, char **env);
char				*ft_special_caract(char *result, char *var);
char				**ft_argv(char **argv, char *arg);
char				**ft_red(char **argv, char *arg);
#endif