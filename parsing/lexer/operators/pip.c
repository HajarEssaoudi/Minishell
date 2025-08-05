/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 08:50:35 by mabdelha          #+#    #+#             */
/*   Updated: 2025/08/05 04:15:54 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing.h"

int	check_after_befor_pip(int *i, char *input, int len)
{
	int	j;

	j = 0;
	if (*i == 0 || *i == len - 1 || len == 0 || (len == 1 && input[0] == '|'))
	{
		ft_printf(2, "Minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	j = *i - 1;
	while (j >= 0 && input[j] == ' ')
		j--;
	if (j < 0)
	{
		ft_printf(2, "Minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	j = *i + 1;
	while (input[j] && input[j] == ' ')
		j++;
	if (!input[j] || input[j] == '|')
	{
		ft_printf(2, "Minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}

int	check_pip(char *input)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(input);
	while (input[i])
	{
		if (input[i] == '|')
		{
			if (input[i + 1] == '|')
			{
				ft_printf(2,
					"Minishell: syntax error near unexpected token `||'\n");
				return (1);
			}
			if ((check_after_befor_pip(&i, input, len)))
				return (1);
		}
		i++;
	}
	return (0);
}

t_lexer	*handle_pip(char *input, int *i, t_lexer *div)
{
	if (!check_pip(input))
	{
		add_ch(&div, "pip", "|", "0");
		(*i)++;
	}
	else
		return (NULL);
	return (div);
}
