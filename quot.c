#include "lib/libft.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*check_quot(char *input, int k, char quot, char **cp_env)
{
    int i = k;
	int j = ++i;
	while (input[i] && input[i] != quot)
		i++;
    printf ("%c\n", input[i]);
	if (input[i] && input[i] == quot)
	{
		char *str;
		if (quot == '"')
		{
			str = ft_strdup(ft_var(ft_substr(input, j, i - j), cp_env));
		}
		else
			str = ft_substr(input, j, i - j);
		return (str);
	}
	else
	{
		printf("zsh: parse error near '%c'\n", quot);
		return (NULL);
	}
}
