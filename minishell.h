#ifndef MINISHELL_H
#define MINISHELL_H


int check_redirect(char *input);
int	check_pip(char *input);
char *get_env_var(char **cp_env, char *key);
char	*check_quot(char *input, int i, char quot, char **cp_env);
char *ft_var(char *str, char **cp_env);

#endif
