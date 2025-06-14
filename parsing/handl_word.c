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
	str = ft_strdup("");
	while (*var)
	{
		str = ft_strjoin(str, *var);
		var++;
	}
	free(sub);
	// free_str(var, 0);
	if (input[*i] == '"')
	{
		quot = ft_str(input, i, cp_env);
		if (*quot)
		{
			while (*quot)
			{
				sub = ft_strjoin(str, *quot);
				quot++;
			}
			free(str);
			str = sub;
			free_str(quot, 0);
		}
		else
			return (NULL);
	}
	var = ft_split(str, ' ');
	return (var);
}

char	**ft_add_str(char **str, char *input, int *i, char **cp_env, int j)
{
	char	*sub;
	char	**var;
	char	*s;
	char	**new;

	sub = ft_substr(input, j, *i - j);
	var = ft_var(sub, cp_env, input[*i]);
	while (*var)
	{
		while (*str)
			str++;
		s = ft_strjoin(*str, *var);
		var++;
	}
	free_str(str, 0);
	free(sub);
	free_str(var, 0);
	if (input[*i] == '"')
	{
		new = ft_str(input, i, cp_env);
		if (!new)
			return (NULL);
		else
			s = ft_strjoin(s, *new);
		free_str(new, 0);
	}
	var = ft_split(s, ' ');
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
		if (!str)
			return (NULL);
	}
	j = *i;
	while (input[*i] && input[*i] != '>' && input[*i] != '<' && input[*i] != '|'
		&& input[*i] != ' ' && input[*i] != '"' && input[*i] != '\'')
		(*i)++;
	if (j != *i)
	{
		if (str)
			str = ft_add_str(str, input, i, cp_env, j);
		else
			str = ft_new_str(input, i, cp_env, j);
	}
	return (str);
}

t_lexer	*get_str(char *input, int *i, t_lexer *lexer, char **cp_env)
{
	char	**str;

	str = ft_str(input, i, cp_env);
	if (!str)
		return (NULL);
	if (!*str)
	{
		while (*str)
		{
			add_ch(&lexer, "string", *str);
			str++;
		}
		free_str(str, 0);
	}
	return (lexer);
}
