/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 01:33:48 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/05 01:34:04 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char	*expand_exit_status(char *tmp1, int *k, int exit_status)
{
	char	*val;
	char	*tmp;

	val = ft_itoa(exit_status);
	tmp = ft_strjoin(tmp1, val);
	free(tmp1);
	free(val);
	(*k) += 2;
	return (tmp);
}

char	*expand_variable(char *line , char *tmp1, char **env, int *k)
{
	char	*tmp2;
	char	*tmp;
	char	*val;
	int		var_start;

	(*k)++;
	var_start = *k;
	while (line[*k] && (ft_isalpha(line[*k]) || line[*k] == '_'))
		(*k)++;
	tmp2 = ft_substr(line, var_start, *k - var_start);
	val = ft_var(tmp2, env);
	tmp = ft_strjoin(tmp1, val);
	free(tmp1);
	free(tmp2);
	return (tmp);
}

char	*other_character(char *line, char *tmp1, int *k)
{
	char	*tmp2;
	char	*tmp;

	if (line[*k] == '$' && line[*k + 1] != '$')
	{
		tmp2 = ft_substr(line, *k, 2);
		(*k) += 2;
	}
	else
	{
		tmp2 = ft_substr(line, *k, 1);
		(*k)++;
	}
	tmp = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	return (tmp);
}

char	*simple_character(char *line, char *tmp1, int *k)
{
	char	*tmp2;
	char	*tmp;
	int		start;

	start = *k;
	while (line[*k] && line[*k] != '$')
		(*k)++;
	tmp2 = ft_substr(line, start, *k - start);
	tmp = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	return (tmp);
}

char	*ft_expand(char *line, char **env, int exit_status)
{
	char	*tmp1 = ft_strdup("");
	char	*tmp2;
	char	*tmp;
	char	*val;
	int		k = 0;
	int		var_start, start;

	if (!tmp1)
		return (NULL);

	while (line[k])
	{
		if (line[k] == '$' && line[k + 1] == '?')
			tmp1 = expand_exit_status(tmp1, &k, exit_status);
		else if (line[k] == '$' && (ft_isalpha(line[k + 1]) || line[k + 1] == '_'))
			tmp1 = expand_variable(line, tmp1, env, &k);
		else if (line[k] == '$')
			tmp1 = other_character(line, tmp1, &k);
		else
			tmp1 = simple_character(line, tmp1, &k);
	}
	return (tmp1);
}

