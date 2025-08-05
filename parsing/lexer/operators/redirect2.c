/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 08:51:56 by mabdelha          #+#    #+#             */
/*   Updated: 2025/08/05 08:14:45 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing.h"

static int	skip_spaces(const char *input, int i)
{
	while (input[i] && input[i] == ' ')
		i++;
	return (i);
}

static int	check_herdoc(char *input, int *k)
{
	if (input[*k + 1] != '<' && input[*k + 2] != '<')
	{
		ft_printf(2, "Minishell: syntax error near unexpected token `<'\n");
		return (1);
	}
	else if (input[*k] == '<' && input[*k + 1] == '<' && input[*k + 2] != '<')
	{
		ft_printf(2, "Minishell: syntax error near unexpected token `<<'\n");
		return (1);
	}
	else if (input[*k] == '<' && input[*k + 1] == '<' && input[*k + 2] == '<')
	{
		ft_printf(2, "Minishell: syntax error near unexpected token `<<<'\n");
		return (1);
	}
	else if (input[*k] == '<' && input[*k + 1] == '>')
	{
		ft_printf(2, "Minishell: syntax error near unexpected token `<>'\n");
		return (1);
	}
	return (0);
}

static int	check_append(int *k, char *input)
{
	if (input[*k] == '>' && input[*k + 1] != '>')
	{
		ft_printf(2, "Minishell: syntax error near unexpected token `>'\n");
		return (1);
	}
	if (input[*k] == '>' && input[*k + 1] == '>')
	{
		ft_printf(2, "Minishell: syntax error near unexpected token `>>'\n");
		return (1);
	}
	return (0);
}

static int	check_last(int i, char *input)
{
	int	k;

	k = ++i;
	k = skip_spaces(input, k);
	if (input[k] == '|')
	{
		ft_printf(2, "Minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	else if (input[k] == '>')
		return (check_append(&k, input));
	else if (input[k] == '<')
		return (check_herdoc(input, &k));
	else if (input[k] == '\0')
	{
		ft_printf(2,
			"Minishell: syntax error near unexpected token `newline'\n");
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
		if ((input[i] == '>' && input[i + 1] == '>') || (input[i] == '<'
				&& input[i + 1] == '<'))
		{
			i++;
			if (check_last(i, input))
				return (1);
		}
		if (input[i])
			i++;
	}
	return (0);
}
