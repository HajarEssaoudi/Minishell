/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdelhaqmarouan <abdelhaqmarouan@student.42.fr>  #+#  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-22 20:59:59 by abdelhaqmarouan   #+#    #+#             */
/*   Updated: 2025-07-22 20:59:59 by abdelhaqmarouan  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing.h"

char	*ft_join(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (result);
}

char	*norm_variable_word(char *input, t_str_list *str_list)
{
	char	*result;
	char	*tmp;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (input[i])
	{
		if (input[i] == '$' && (ft_isalpha(input[i + 1]) || input[i + 1] == '_')
			&& ft_strcmp(str_list->flag, "1"))
			tmp = expand_var(input, &i, str_list);
		else if (input[i] == '$' && ((!ft_isalpha(input[i + 1]) || input[i
						+ 1] != '_') || !ft_strcmp(str_list->flag, "1")))
			tmp = expand_exit(input, &i, str_list);
		else
			tmp = string_norm(input, &i);
		result = ft_join(result, tmp);
	}
	return (result);
}

int	handl_quote(char *input, int i, t_split **split, t_str_list *str_list)
{
	char	quot;
	char	*var_quot;
	char	*result;
	int		j;

	quot = input[i];
	j = ++i;
	while (input[i] && input[i] != quot)
		i++;
	var_quot = ft_substr(input, j, i - j);
	i++;
	if (quot == '"')
	{
		result = norm_variable_word(var_quot, str_list);
		add_split(split, result, 1, str_list->flag);
		free(result);
	}
	else
		add_split(split, var_quot, 1, str_list->flag);
	free(var_quot);
	return (i);
}

int	handl_unquote(char *input, int i, t_split **split, t_str_list *str_list)
{
	char	*var;
	char	*result;
	int		j;

	j = i;
	while (input[i] && input[i] != '"' && input[i] != '\'')
		i++;
	var = ft_substr(input, j, i - j);
	result = norm_variable_word(var, str_list);
	if (result && (result[0] != '\0' || (result[0] == '\0'
				&& !ft_strcmp(str_list->flag, "2"))))
		add_split(split, result, 0, str_list->flag);
	free(result);
	free(var);
	return (i);
}

t_lexer	*get_str(char *input, t_lexer *lexer, char **cp_env, char *flag)
{
	int			i;
	t_split		*split;
	t_str_list	str_list;

	split = NULL;
	i = 0;
	str_list.flag = flag;
	str_list.env = cp_env;
	str_list.lexer = lexer;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			i = handl_quote(input, i, &split, &str_list);
			if (i == -1)
				return (NULL);
		}
		else
			i = handl_unquote(input, i, &split, &str_list);
	}
	lexer = ft_final(lexer, split);
	return (lexer);
}
