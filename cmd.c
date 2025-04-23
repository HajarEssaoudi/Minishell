#include "lib/libft.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char    *check_ext(char *input, char **cp_env)
{
	int		i;
	int		j;
	char	*path;
	char	**path_split;
	char	*cmd;

	i = 0;
	j = 0;
	path = get_env_var(cp_env, "PATH");
	path_split = ft_split(path, ':');
	while (path_split[i])
	{
		cmd = ft_strjoin(path_split[i], "/");
		cmd = ft_strjoin(cmd, input);
		if (access(cmd, F_OK) == 0)
		{
            // free(path);
			free(path_split);
			return (cmd);
		}
		free(cmd);
		i++;
	}
	free(path_split);
	return (NULL);
}
char	*check_in(char *input, char **cp_env)
{
	char	*cmd[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (ft_strncmp(input, cmd[i], ft_strlen(cmd[i])) == 0)
		{
			return (cmd[i]);
		}
		i++;
	}
	return (NULL);
}
char    *replace_path(char *path, char *cmd)
{
    free (cmd);
    cmd = ft_strdup(path);
    return (cmd);
}

t_tok	*check_cmd(t_tok *tok, char **cp_env)
{
    t_tok   *tmp = tok;
    while (tok)
    {
        if (tok->path[0] != '/')
        {
            char    *in = check_in(tok->path, cp_env);
            char    *ex = check_ext(tok->path, cp_env);
            if (in)
                tok->path = replace_path(in, tok->path);
            else if (ex)
                tok->path = replace_path(ex, tok->path);
            else if (!in && !ex)
                return (NULL);
        }
        tok = tok->next;
    }
    return (tmp);
}
