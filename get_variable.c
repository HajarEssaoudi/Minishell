/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 00:11:02 by mabdelha          #+#    #+#             */
/*   Updated: 2025/04/23 15:28:03 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_var(char **cp_env, char *var)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(var);
	while (cp_env[i])
	{
		if (ft_strncmp(cp_env[i], var, len) == 0 && cp_env[i][len] == '=')
			return (&cp_env[i][len + 1]);
		i++;
	}
	return (NULL);
}

static char	*handle_tilde(char *result, char **cp_env, int *i)
{
	char	*val;
	char	*tmp;

	val = get_env_var(cp_env, "HOME");
	if (val)
		tmp = ft_strjoin(result, val);
	else
		tmp = ft_strjoin(result, "");
	free(result);
	(*i)++;
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
	// result = tmp;
	free(var);
	return (tmp);
}

static char	*handle_normal_char(char *result, char c)
{
	char	tmp_char[2];
	char	*tmp_result;

	tmp_char[0] = c;
	tmp_char[1] = '\0';
	tmp_result = ft_strjoin(result, tmp_char);
	free(result);
	return (tmp_result);
}

char	*cv_var(char *str, int *i)
{
	int		j;
	char	*var;
	// while (str[*i] && (str[*i] == '~' || str[*i] == '=' || str[*i] == '^'))
	// 	(*i)++;
	if (str[*i] && !(ft_isdigit(str[*i])))
	{
		j = *i;
		while ((ft_isalpha(str[*i]) || str[*i] == '_') && str[*i])
			(*i)++;
		var = ft_substr(str, j, *i - j);
		return (var);
	}
	else if (str[*i] && ft_isdigit(str[*i]))
	{
		(*i)++;
		return (ft_strdup("1"));
	}
	return (NULL);
}

char	*ft_dollar(char *str, char **cp_env, char *result, int *i)
{
	char	*var;
	(*i)++;
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
		else if (ft_strncmp(var, "1", 1) == 0)
		{
			(*i)++;
			free(var);
			return (result);
		}
		else
			result = handle_simple_var(result, var, cp_env, i);
	}
	return (result);
}
char	*ft_var(char *str, char **cp_env, char input)
{
	int		i;
	char	*result;

	i = 0;
	result = malloc(1);
	result[0] = '\0';
	while (str[i])
	{
		
		if (str[i] == '~' && (i == 0 || str[i - 1] == ' ') &&
            (str[i + 1] == '/' || str[i + 1] == '\0' || str[i + 1] == ' ') && (input != '"' && input != '\''))
		{
			printf ("%c\n", input);
			result = handle_tilde(result, cp_env, &i);
		}
		if (str[i] == '$' && (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
			result = ft_dollar(str, cp_env, result, &i);
		else
			result = handle_normal_char(result, str[i++]);
	}
	return (result);
}
