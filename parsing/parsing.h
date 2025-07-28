/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 09:45:17 by mabdelha          #+#    #+#             */
/*   Updated: 2025/07/24 01:56:13 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../ft_printf/ft_printf.h"
# include "../lib/libft.h"
# include <ctype.h>
# include <errno.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>

typedef struct s_rederict
{
	char				*type;
	char				*filename;
	char				*flag;
	struct s_rederict	*next;
}						t_rederict;

typedef struct s_tok
{
	char				**str;
	char				*execute;
	char				*path;
	t_rederict			*redirect;
	int					heredoc_fd;
	char				*pip;
	char				**env;
	char				*pwd;
	char				*old_pwd;
	int					quot;
	unsigned char		exit_status;
	struct s_tok		*next;
}						t_tok;

typedef struct s_lexer
{
	char				*flag;
	char				*args;
	char				*type;
	char				*ambg;
	int					quot;
	int					exit_status;
	struct s_lexer		*next;
}						t_lexer;

typedef struct s_quot
{
	int					start;
	int					i;
	char				*str;
	char				*sub;
}						t_quot;

typedef struct s_split
{
	char				*str;
	int					first_space;
	int					last_space;
	int					quoted;
	char				*flag;
	struct s_split		*next;
}						t_split;

typedef struct s_str_list
{
	char				**env;
	t_lexer				*lexer;
	char				*flag;
}						t_str_list;

typedef struct s_lexer_final
{
	char				*amg;
	t_lexer				**lexer;
	char				**final_split;
}						t_lexer_final;

t_lexer					*ft_lexer(char *input, char **env, int exit_status);
char	**ft_split_final(char const *s);
int						is_word(char c);
char					**copy_env(char **env);
char					*get_env_var(char **cp_env, char *var);
t_lexer					*handle_pip(char *input, int *i, t_lexer *div);
t_lexer					*ft_operator(char *input, int *i, t_lexer *lexer);
t_lexer					*get_str(char *input, t_lexer *lexer, char **cp_env,
							char *flag);
t_lexer					*ft_word(t_lexer *lexer, char *input, int *i,
							char **env);
t_lexer					*ft_final(t_lexer *lexer, t_split *split);
t_tok					*get_tok(char *prompt, char **env, int exit_status);
void					ft_amg(t_lexer *lexer);
int						check_redirect2(char *input);
int						check_redirect1(char *input);
char					*expand_exit(char *input, int *i, t_str_list *str_list);
char					*expand_var(char *input, int *i, t_str_list *list_str);
int						skip_space_tab_newline(char *str, int i);
void					ft_type(t_lexer *lexer);
char					*string_norm(char *input, int *i);
char					*final_spaces(char *final, t_lexer_final *lexer_final);
char					*fin_last_space(char *final,
							t_lexer_final *lexer_final);
char					*fin_first_space(char *final,
							t_lexer_final *lexer_final);
char					*fin_no_spaces(char *final, t_lexer_final *lexer_final);
void					add_lexer(t_lexer *lexer, t_lexer *token);
void					add_ch(t_lexer **lexer, char *type, char *input,
							char *ambg);
void					add_split(t_split **split, char *str, int quoted,
							char *flag);
void					free_tok(t_tok *tok);
void					free_lexer(t_lexer *lexer);
void					free_str(char **str);
char					**ft_red(char **argv, char *arg);
char					**ft_argv(char **argv, char *arg);
char					*ft_var(char *str, char **cp_env);
void					add_middel_split(t_lexer_final *lexer_final, int j);
int						count_final_split(t_lexer_final *lexer_final);
#endif