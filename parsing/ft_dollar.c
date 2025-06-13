/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 02:53:54 by mabdelha          #+#    #+#             */
/*   Updated: 2025/06/12 18:49:12 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*handle_simple_var(char *result, char *var, char **cp_env, int *i)
{
	char	*val;
	char	*tmp;

	val = get_env_var(cp_env, var);
	if (val)
		tmp = ft_strjoin(result, val);
	else
		tmp = ft_strdup(result);
	free(result);
	free(var);
	return (tmp);
}

static char	*handle_braces_var(char *result, char *str, char **cp_env, int *i)
{
	int		start;
	char	*var;
	char	*val;
	char	*tmp;

	(*i)++;
	start = *i;
	while (str[*i] && str[*i] != '}')
		(*i)++;
	if (str[*i] == '}')
	{
		var = ft_substr(str, start, *i - start);
		val = get_env_var(cp_env, var);
		if (val)
			tmp = ft_strjoin(result, val);
		else
			tmp = ft_strdup(result);
		free(result);
		result = tmp;
		free(var);
		(*i)++;
	}
	return (result);
}

char	*cv_var(char *str, int *i)
{
	int		j;
	char	*var;

	j = 1;
	while (str[j])
	{
		if (!ft_isalpha(str[j]) && !ft_isdigit(str[j]))
			break ;
		j++;
	}
	if (!str[j])
	{
		j = *i;
		while ((ft_isalpha(str[*i]) || str[*i] == '_') && str[*i])
			(*i)++;
		var = ft_substr(str, j, *i - j);
		return (var);
	}
	else
	{
		while (str[*i])
			(*i)++;
		return (ft_substr(str, j, *i - j));
	}
	return (NULL);
}

char	*ft_dollar(char *str, char **cp_env, char *result, int *i)
{
	char	*var;

	(*i)++;
	var = NULL;
	if (str[*i] == '{')
		result = handle_braces_var(result, str, cp_env, i);
	else
	{
		var = cv_var(str, i);
		if (!var)
		{
			free(result);
			return (NULL);
		}
		else if (!ft_isdigit(var[0]) && !ft_isalpha(var[0]))
		{
			(*i)++;
			result = ft_special_caract(result, var);
		}
		else
			result = handle_simple_var(result, var, cp_env, i);
	}
	return (result);
}
