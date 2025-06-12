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

char	*ft_new_str(char *input, int *i, char **cp_env, int j)
{
	char	*sub;
	char	*var;
	char	*str;
	char	*quot;

	sub = ft_substr(input, j, *i - j);
	var = ft_var(sub, cp_env, input[*i]);
	str = ft_strdup(var);
	free(sub);
	free(var);
	if (input[*i] == '"')
	{
		quot = ft_str(input, i, cp_env);
		if (quot)
		{
			sub = ft_strjoin(str, quot);
			free(str);
			str = sub;
			free(quot);
		}
		else
			return (NULL);
	}
	return (str);
}

char	*ft_add_str(char *str, char *input, int *i, char **cp_env, int j)
{
	char	*sub;
	char	*var;
	char	*s;
	char	*new;

	sub = ft_substr(input, j, *i - j);
	var = ft_var(sub, cp_env, input[*i]);
	s = ft_strjoin(str, var);
	free(str);
	free(sub);
	free(var);
	if (input[*i] == '"')
	{
		new = ft_str(input, i, cp_env);
		if (!new)
			return (NULL);
		else
			s = ft_strjoin(s, new);
		free(new);
	}
	return (s);
}

char	*ft_str(char *input, int *i, char **cp_env)
{
	char	*str;
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
	char	*str;

	str = ft_str(input, i, cp_env);
	if (!str)
		return (NULL);
	if (*str != '\0')
	{
		add_ch(&lexer, "string", str);
		free(str);
	}
	return (lexer);
}
