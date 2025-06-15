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
	char	*tmp;
	int		k;

	sub = ft_substr(input, j, *i - j);
	var = ft_var(sub, cp_env, input[*i]);
	free(sub);
<<<<<<< HEAD
	str = ft_strdup("");
	k = 0;
	while (var && var[k])
	{
		tmp = ft_strjoin(str, var[k]);
		free(str);
		str = tmp;
		k++;
	}
	free_str(var, 0);
	if (input[*i] == '"')
=======
	free(var);
	if (input[*i] == '"' || input[*i] == '\'')
>>>>>>> 47f99e9 (fixe error)
	{
		quot = ft_str(input, i, cp_env);
		k = 0;
		if (quot[k])
		{
			while (quot[k])
			{
				tmp = ft_strjoin(str, quot[k]);
				free(str);
				str = tmp;
				k++;
			}
			free_str(quot, 0);
			free(str);
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
	char	*tmp;
	char	**new;
	char	**result;
	int		k;

	sub = ft_substr(input, j, *i - j);
	var = ft_var(sub, cp_env, input[*i]);
	free(sub);
<<<<<<< HEAD
	s = ft_strdup("");
	k = 0;
	while (str[k])
	{
		tmp = ft_strjoin(s, str[k]);
		free(str);
		str = tmp;
		k++;
	}
	free_str(str, 0);
	k = 0;
	while (var[k])
	{
		tmp = ft_strjoin(s, var[k]);
		free(s);
		s = tmp;
		k++;
	}
	free_str(var, 0);
	if (input[*i] == '"')
=======
	free(var);
	if (input[*i] == '"' || input[*i] == '\'')
>>>>>>> 47f99e9 (fixe error)
	{
		new = ft_str(input, i, cp_env);
		if (!new)
			return (NULL);
		k = 0;
		while (new[k])
		{
			tmp = ft_strjoin(s, new[k]);
			free(s);
			s = tmp;
			k++;
		}
		free_str(new, 0);
	}
	result = ft_split(s, ' ');
	free(s);
	return (result);
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
