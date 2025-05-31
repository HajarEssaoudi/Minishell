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

void add_ch(t_div **div, char *type, char *input)
{
	t_div *token;
	t_div *tmp;

	token = malloc(sizeof(t_div) + 1);
	token->args = ft_strdup(input);
	token->type = ft_strdup(type);
	token->next = NULL;
	if (!*div)
	{
		*div = token;
		// free_div(token);
	}
	else
	{
		tmp = *div;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = token;
		// free_div(token);
	}
	// free_div(token);
}

t_div *get_str(char *input, int *i, t_div *div, char **cp_env)
{
	char *str;

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

t_div *ft_div(char *input, char **cp_env)
{
	int i;
	t_div *div;

	i = 0;
	div = NULL;
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (!input[i] && ft_strlen(input) == 0)
			return NULL;
		else if (!input[i] && div)
			return div;
		else if (input[i] == '|' || input[i] == '>' || input[i] == '<')
		{
			div = ft_operator(input, &i, div);
			if (!div)
			{
				free_div(div);
				return (NULL);
			}
		}
		else if (input[i])
		{
			div = get_str(input, &i, div, cp_env);
			if (!div)
			{
				free_div(div);
				return (NULL);
			}
		}
	}
	return (div);
}
