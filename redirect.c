#include "lib/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	check_redirect(char *input)
{
	int i = 0;
	while (input[i])
	{
        if (input[i] == '>' && input[i + 1] == ' ')
		{
			i++;
			while (input[i] == ' ')
				i++;
			if (input[i] == '>')
			{
				printf("zsh: parse error near '>'\n");
				return (1);
			}
			
		}
		if (i == 0 && (input[i] == '>' || (input[i] == '>' && input[1 + 1] == '>')))
		{
			printf("zsh: parse error near '\\n'\n");
			return (1);
		}
		else if (i == 0 && (input[0] == '<' || (input[0] == '<' && input[1] == '<')))
		{
			printf("zsh: parse error near '\\n'\n");
			return (1);
		}
		else if (input[i] == '>' && (input[i + 1] == '\0' || input[i + 1] == '|'
				|| input[i + 1] == '<'))
		{
			printf("zsh: parse error near '>'\n");
			return (1);
		}
		if (input[i] == '>' && input[i + 1] == '>' && (input[i + 2] == '\0'
				|| input[i + 2] == '|' || input[i + 2] == '<'))
		{
			printf("zsh: parse error near '>>'\n");
			return (1);
		}
		if (input[i] == '<' && (input[i + 1] == '\0' || input[i + 1] == '|'
				|| input[i + 1] == '>'))
		{
			printf("zsh: parse error near '<'\n");
			return (1);
		}
		if (input[i] == '<' && input[i + 1] == '<' && (input[i + 2] == '\0'
				|| input[i + 2] == '|' || input[i + 2] == '>'))
		{
			printf("zsh: parse error near '<<'\n");
			return (1);
		}
		i++;
	}
    return (0);
}