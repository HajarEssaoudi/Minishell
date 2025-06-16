/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 01:39:53 by mabdelha          #+#    #+#             */
/*   Updated: 2025/06/12 18:49:39 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**ft_new_str(char *input, int *i, char **cp_env, int j)
{
	char	*sub;
	char	**var;
	char	*str;
	char	**quot;

	sub = ft_substr(input, j, *i - j);
	var = ft_var(sub, cp_env, input[*i]);
	// str = ft_strdup(var);
	// free(sub);
	// free(var);
	if (input[*i] == '"' || input[*i] == '\'')
	{
		quot = ft_str(input, i, cp_env);
		if (quot && quot[0])
		{
			int k = 0;
			while (var[k])
				k++;
			k--;
			sub = ft_strjoin(var[k], quot[0]);
			free(str);
			var[k] = sub;
			// free(quot);
		}
		else
			return (NULL);
	}
	return (var);
}

char	**ft_add_str(char *str, char *input, int *i, char **cp_env, int j)
{
	char	*sub;
	char	**var;
	char	*s;
	char	**new;

	sub = ft_substr(input, j, *i - j);
	var = ft_var(sub, cp_env, input[*i]);
	s = ft_strjoin(str, var[0]);
	free(str);
	free(sub);
	free(var[0]);
	var[0] = s;
	if (input[*i] == '"' || input[*i] == '\'')
	{
		int k = 0;
		while (var[k])
			k++;
		k--;
		new = ft_str(input, i, cp_env);
		if (!new)
			return (NULL);
		else
			var[k] = ft_strjoin(var[k], new[0]);
		// free(new);
	}
	return (var);
}

char	**ft_str(char *input, int *i, char **cp_env)
{
	char	**str;
	int		j;

	str = NULL;
	if (input[*i] == '"' || input[*i] == '\'')
	{
		str = check_quot(input, i, input[*i], cp_env);
		if (!str[0])
			return (NULL);
	}
	j = *i;
	while (input[*i] && input[*i] != '>' && input[*i] != '<' && input[*i] != '|'
		&& input[*i] != ' ' && input[*i] != '"' && input[*i] != '\'')
		(*i)++;
	if (j != *i)
	{
		if (str)
		{
			int k = 0;
			while (str[k])
				k++;
			str = ft_add_str(str[k - 1], input, i, cp_env, j);
		}
		else
			str = ft_new_str(input, i, cp_env, j);
	}
	return (str);
}

t_lexer	*get_str(char *input, int *i, t_lexer *lexer, char **cp_env)
{
	char	**str;
	char	**tmp;
	char	*init_str;
	int k = 0;
	str = ft_str(input, i, cp_env);
	if (!str)
		return (NULL);
	while (input[*i] == '"' || input[*i] == '\'')
	{
		k = 0;
		tmp = ft_str(input, i, cp_env);
		while (str[k])
			k++;
		k--;
		init_str = ft_strjoin(str[k], tmp[0]);
		free(str[k]);
		// free(tmp);
		str[k] = init_str;
	}
	k = 0;
	while (str[k])
	{
		add_ch(&lexer, "string", str[k]);
		free(str[k]);
		k++;
	}
	return (lexer);
}
