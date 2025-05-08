/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   div.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-23 02:22:57 by mabdelha          #+#    #+#             */
/*   Updated: 2025/05/05 02:22:30 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_ch(t_div **div, char *type, char *input)
{
	t_div	*token;
	t_div	*tmp;

	token = malloc(sizeof(t_div));
	token->args = ft_strdup(input);
	token->type = ft_strdup(type);
	token->next = NULL;
	if (!*div)
		*div = token;
	else
	{
		tmp = *div;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = token;
	}
}

t_div	*handle_pip(char *input, int *i, t_div *div)
{
	if (!check_pip(input))
	{
		add_ch(&div, "pip", "|");
		(*i)++;
	}
	else
		return (NULL);
	return	(div);
}

t_div	*handle_redirect_output(char *input, int *i, t_div *div)
{
	if (!check_redirect1(input))
	{
		add_ch(&div, "output", ">");
		(*i)++;
	}
	else
		return (NULL);
	return (div);
}

t_div	*handle_redirect_input(char *input, int *i, t_div *div)
{
	if (!check_redirect1(input))
	{
		add_ch(&div, "input", "<");
		(*i)++;
	}
		else
			return (NULL);
	return (div);
}

t_div	*handle_redirect_append(char *input, int *i, t_div *div)
{
	if (!check_redirect2(input))
	{
		add_ch(&div, "append", ">>");
		(*i)++;
	}
		else
			return (NULL);
	return (div);
}

t_div	*handle_redirect_heredoc(char *input, int *i, t_div *div)
{
	if (!check_redirect2(input))
	{
		add_ch(&div, "heredoc", "<<");
		(*i)++;
	}
		else
			return (NULL);
	return (div);
}

t_div	*ft_operator(char *input, int *i, t_div *div)
{
	if (input[*i] == '|')
		div = handle_pip(input, i, div);
	else if (input[*i] == '>' && input[*i + 1] != '>')
		div = handle_redirect_output(input, i, div);
	else if (input[*i] == '<' && input[*i + 1] != '<')
		div = handle_redirect_input(input, i, div);
	else if (input[*i] == '>' && input[*i + 1] == '>')
		div = handle_redirect_append(input, i, div);
	else if (input[*i] == '<' && input[*i + 1] == '<')
		div = handle_redirect_heredoc(input, i, div);
	else if (!div)
		return (NULL);
	return (div);
}

t_div	*get_str(char *input, int *i, t_div *div, char **cp_env)
{
	char	*str;

	str = ft_str(input, i, cp_env);
	if (!str)
		return NULL;
	if (*str != '\0')
	{
		add_ch(&div, "string", str);
		free(str);
	}
	return (div);
}

t_div	*ft_div(char *input, char **cp_env)
{
	int		i;
	t_div	*div;

	i = 0;
	div = NULL;
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (!input[i] && ft_strlen(input) == 0)
			exit(1);
		if (input[i] == '|' || input[i] == '>' || input[i] == '<')
		{
			div = ft_operator(input, &i, div);
			if (!div)
				return (NULL);
		}
		else if (input[i])
		{
			div = get_str(input, &i, div, cp_env);
			if (!div)
				return (NULL);
		}
	}
	return (div);
}
