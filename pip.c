#include "minishell.h"

int	check_pip(char *input)
{
	int	i;
	int	len;
	int	j;

	i = 0;
	len = ft_strlen(input);
    //hadi w quot w redirect w redirect2 wakha tkon smitek hajar 4atfhmihom hihihi
	if (len == 0 || (len == 1 && input[0] == '|'))
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	while (input[i])
	{
		if (input[i] == '|')
		{
			if (input[i + 1] == '|')
			{
				printf("minishell: syntax error near unexpected token `||'\n");
				return (1);
			}
			if (i == 0)
			{
				printf("minishell: syntax error near unexpected token `|'\n");
				return (1);
			}
			if (i == len - 1)
			{
				printf("minishell: syntax error near unexpected token `|'\n");
				return (1);
			}
			j = i - 1;
			while (j >= 0 && input[j] == ' ')
				j--;
			if (j < 0)
			{
				printf("minishell: syntax error near unexpected token `|'\n");
				return (1);
			}
			j = i + 1;
			while (input[j] && input[j] == ' ')
				j++;
			if (!input[j])
			{
				printf("minishell: syntax error near unexpected token `|'\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}
