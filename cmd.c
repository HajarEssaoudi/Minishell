#include "lib/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minishell.h"

int check_path(char *input, char **cp_env)
{
    int i = 0;
    int j = 0;
    char *path = get_env_var(cp_env, "PATH");
    char **path_split = ft_split(path, ':');
    
    
}
int check_cmd(char *input, char **cp_env)
{
    char *cmd[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
    char
}