/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 03:34:52 by mabdelha          #+#    #+#             */
/*   Updated: 2025/04/29 16:34:26 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_spaces(const char *input, int i)
{
	while (input[i] && input[i] == ' ')
		i++;
	return (i);
}

static int	check_out(int *k, char *input)
{
	if (input[*k + 1] != '>')
	{
		printf("Minishell: syntax error near unexpected token `>'\n");
		return (1);
	}
	else if (input[*k] == '|')
	{
		printf("Minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	else if (input[*k] == '>' && input[*k + 1] == '>')
	{
		printf("Minishell: syntax error near unexpected token `>>'\n");
		return (1);
	}
	return (0);
}

static int	check_in(char *input, int *k)
{
	if (input[*k + 1] != '<' && input[*k + 1] != '>')
	{
		printf("Minishell: syntax error near unexpected token `<'\n");
		return (1);
	}
	else if (input[*k + 1] == '<' && input[*k + 2] != '<')
	{
		printf("Minishell: syntax error near unexpected token `<<'\n");
		return (1);
	}
	else if (input[*k + 1] == '<' && input[*k + 2] == '<')
	{
		printf("Minishell: syntax error near unexpected token `<<<'\n");
		return (1);
	}
	else if (input[*k + 1] == '>')
	{
		printf("Minishell: syntax error near unexpected token `<>'\n");
		return (1);
	}
	return (0);
}

static int	check_last(int i, char *input)
{
	int	k;

	k = ++i;
	while (input[k] == ' ')
		k++;
	if (input[k] == '>')
		return (check_out(&k, input));
	else if (input[k] == '<')
		return (check_in(input, &k));
	else if (!input[k])
	{
		printf("Minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

int	check_redirect(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		i = skip_spaces(input, i);
		if ((input[i] == '>' && input[i + 1] != '>') || (input[i] == '<'
				&& input[i + 1] != '<'))
		{
			if (check_last(i, input))
				return (1);
		}
		i++;
	}
	return (0);
}
