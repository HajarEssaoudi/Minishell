#include "lib/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int	skip_spaces(const char *input, int i)
{
	while (input[i] && input[i] == ' ')
		i++;
	return i;
}

static void	syntax_error(const char *token)
{
	printf("zsh: parse error near `%s`\n", token);
}

int	check_redirect(char *input)
{
	int	i = 0;

	while (input[i])
	{
		i = skip_spaces(input, i);
		if (input[i] == '>')
		{
			if (input[i + 1] == '>' && input[i + 2] == '>')
			{
				syntax_error(">");
				return 1;
			}
			else if (input[i + 1] == '>')
			{
				i += 2;
				i = skip_spaces(input, i);
				if (!input[i] || input[i] == '|' || input[i] == '<' || input[i] == '>')
				{
					syntax_error(">>");
					return 1;
				}
			}
			else
			{
				i++;
				i = skip_spaces(input, i);
				if (!input[i] || input[i] == '|' || input[i] == '<' || input[i] == '>')
				{
					syntax_error(">");
					return 1;
				}
			}
		}
		if (input[i] == '<')
		{
			if (input[i + 1] == '<' && input[i + 2] == '<')
			{
				syntax_error("<");
				return 1;
			}
			else if (input[i + 1] == '<')
			{
				i += 2;
				i = skip_spaces(input, i);
				if (!input[i] || input[i] == '|' || input[i] == '>' || input[i] == '<')
				{
					syntax_error("<<");
					return 1;
				}
			}
			else
			{
				i++;
				i = skip_spaces(input, i);
				if (!input[i] || input[i] == '|' || input[i] == '>' || input[i] == '<')
				{
					syntax_error("<");
					return 1;
				}
			}
		}
		i++;
	}
	return 0;
}
