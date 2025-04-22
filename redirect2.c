#include "minishell.h"

static int	skip_spaces(const char *input, int i)
{
	while (input[i] && input[i] == ' ')
		i++;
	return (i);
}

static int	check_last(int i, char *input)
{
	int	k;

	k = ++i;
	k = skip_spaces(input, k);
	if (input[k] == '>')
	{
		printf ("zsh: parse error near `>'\n");
		return (1);
	}
	 if (input[k] == '>' && input[k + 1] == '>')
	{
		printf ("zsh: parse error near `>>'\n");
		return (1);
	}
	else if (input[k] == '<' && input[k + 1] != '<' && input[k + 1] != '>')
	{
		printf ("zsh: parse error near `<'\n");
		return (1);
	}
	else if (input[k] == '<' && input[k + 1] == '<' && input[k + 2] != '<')
	{
		printf ("zsh: parse error near `<<'\n");
		return (1);
	}
	else if (input[k] == '<' && input[k + 1] == '<' && input[k + 2] == '<')
	{
		printf ("zsh: parse error near `<<<'\n");
		return (1);
	}
	else if (input[k] == '<' && input[k + 1] == '>')
	{
		printf ("zsh: parse error near `<>'\n");
		return (1);
	}
	else if (input[k] == '\0')
	{
		printf("zsh: parse error near `\\n'\n");
		return (1);
	}
	return (0);
}

int	check_redirect2(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		i = skip_spaces(input, i);
		if ((input[i] == '>' && input[i + 1] == '>') || (input[i] == '<' && input[i + 1] == '<'))
		{
			i++;
			if (check_last(i, input))
				return (1);
		}
		i++;
	}
	return (0);
}
