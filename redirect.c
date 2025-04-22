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
	while (input[k] == ' ')
		k++;
	if (input[k] == '>')
	{
		printf ("zsh: parse error near `>'\n");
		return (1);
	}
	else if (input[k] == '|')
	{
		printf ("zsh: parse error near `|'\n");
		return (1);
	}
	else if (input[k] == '>' && input[k + 1] == '>')
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
	else if (!input[k])
	{
		printf("zsh: parse error near `\\n'\n");
		return (1);
	}
	return (0);
}
static void	syntax_error(const char *token)
{
	printf("zsh: parse error near `%s`\n", token);
}

int	check_redirect(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		i = skip_spaces(input, i);
		if ((input[i] == '>' && input[i + 1] != '>') || (input[i] == '<' && input[i + 1] != '<'))
		{
			
			if (check_last(i, input))
				return (1);
		}
		i++;
	}
	return (0);
}
