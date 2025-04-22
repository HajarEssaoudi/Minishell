#include "lib/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minishell.h"

int check_ext(char *input, char **cp_env)
{
    int i = 0;
    int j = 0;
    char *path = get_env_var(cp_env, "PATH");
    char **path_split = ft_split(path, ':');
    while (path_split[i])
    {
        char *cmd = ft_strjoin(path_split[i], "/");
        cmd = ft_strjoin(cmd, input);
        if (access(cmd, F_OK) == 0)
        {
            free(path);
            free(path_split);
            return (1);
        }
        free(cmd);
        i++;
    }
    free(path);
    free(path_split);
    return (0);
}
int check_in(char *input, char **cp_env)
{
    char *cmd[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
    int i = 0;
    while (cmd[i])
    {
        if (ft_strncmp(input, cmd[i], ft_strlen(cmd[i])) == 0)
        {
            return (1);
        }
        i++;
    }
    return (0);
}

int check_cmd(char *input, char **cp_env)
{
    if (check_in(input, cp_env) == 0 && check_ext(input, cp_env) == 0)
    {
        return (0);
    }
    return (1);
}
