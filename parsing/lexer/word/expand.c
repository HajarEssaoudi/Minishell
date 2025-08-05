/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdelhaqmarouan <abdelhaqmarouan@student.42.fr>  #+#  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-23 15:10:27 by abdelhaqmarouan   #+#    #+#             */
/*   Updated: 2025-07-23 15:10:27 by abdelhaqmarouan  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing.h"

char	*expand_var(char *input, int *i, t_str_list *list_str)
{
	int		j;
	char	*val;
	char	*varname;

	j = ++(*i);
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
		(*i)++;
	varname = ft_substr(input, j, *i - j);
	val = ft_var(varname, list_str->env);
	free(varname);
	return (ft_strdup(val));
}

char	*expand_exit(char *input, int *i, t_str_list *str_list)
{
	char	*tmp;

	tmp = NULL;
	if (input[*i + 1] == '?' && ft_strcmp(str_list->flag, "1"))
	{
		tmp = ft_itoa(str_list->lexer->exit_status);
		*i += 2;
	}
	else
	{
		if (input[*i + 1] == '$')
		{
			tmp = ft_substr(input, *i, 1);
			*i += 1;
		}
		else
		{
			tmp = ft_substr(input, *i, 2);
			*i += 2;
		}
	}
	return (tmp);
}

char	*string_norm(char *input, int *i)
{
	int		j;
	char	*tmp;

	tmp = NULL;
	j = *i;
	while (input[*i] && input[*i] != '$')
		(*i)++;
	tmp = ft_substr(input, j, (*i) - j);
	return (tmp);
}
