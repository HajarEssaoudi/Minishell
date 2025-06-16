/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 00:11:02 by mabdelha          #+#    #+#             */
/*   Updated: 2025/06/12 18:49:35 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

char	**ft_var(char *str, char **cp_env, char input)
{
	int		i;
	char	*result;
	char	**split;

	i = 0;
	result = malloc(1);
	result[0] = '\0';
	while (str[i])
	{
		if (str[i] == '~' && (i == 0 || str[i - 1] == ' ') && (str[i + 1] == '/'
				|| str[i + 1] == '\0' || str[i + 1] == ' ') && (input != '"'
				&& input != '\''))
		{
			printf("%c\n", input);
			result = handle_tilde(result, cp_env, &i);
		}
		if (str[i] == '$' && (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
			result = ft_dollar(str, cp_env, result, &i);
		else if (str[i] == '$' && ft_isdigit(str[i + 1]))
			result = handle_normal_char(result, str[i += 2]);
		else
			result = handle_normal_char(result, str[i++]);
	}
	if (input != '"')
	{
		split = ft_split(result, ' ');
		free(result);
	}
	else
	{
		split = malloc(sizeof(char *) * 2);
		split[0] = result;
		split[1] = NULL;
		free(result);
	}
	return (split);
}
