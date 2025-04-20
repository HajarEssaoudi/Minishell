#include "lib/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	check_pip(char *input)
{
	int i = 0;
	while (input[i])
	{
		if (input[i + 1] == '\0')
		{
			printf("zsh: parse error near '|'\n");
			return (1);
		}
		else if (input[i + 1] == '|' || (input[i + 2] == '\0' && input[i + 1] == '|'))
		{
			printf("zsh: parse error near '||'\n");
			return (1);
		}
		else if (i == 0)
		{
			printf("zsh: parse error near '|'\n");
			return (1);
		}
        i++;
	}
    return (0);
}