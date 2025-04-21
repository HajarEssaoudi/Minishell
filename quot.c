#include "minishell.h"

char *check_quot(char *input, int *index, char quot, char **cp_env)
{
    int start = *index + 1;
    int i = start;
    char *str = NULL;

    while (input[i] && input[i] != quot)
        i++;
    if (input[i] == quot)
    {
        if (quot == '"')
        {
            char *sub = ft_substr(input, start, i - start);
            str = ft_var(sub, cp_env);
            free(sub);
        }
        else
        {
            str = ft_substr(input, start, i - start);
        }
        *index = i + 1;
    }
    else
    {
        printf("minishell: syntax error: unclosed `%c' quote\n", quot);
		return (NULL);
    }
    return str;
}
