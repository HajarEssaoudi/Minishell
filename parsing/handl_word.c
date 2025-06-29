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

char	**ft_new_str(char *input, int *i, char **cp_env, int j, char *flag)
{
	char	*sub;
	char	**var;
	char	*str;
	char	**quot;

	sub = ft_substr(input, j, *i - j);
	var = ft_var(sub, cp_env, input[*i], flag);
	// str = ft_strdup(var);
	free(sub);
	// free(var);
	if (input[*i] == '"' || input[*i] == '\'')
	{
		quot = ft_str(input, i, cp_env, flag);
		if (quot && quot[0])
		{
			int k = 0;
			while (var[k])
				k++;
			k--;
			sub = ft_strjoin(var[k], quot[0]);
			// free(str);
			var[k] = sub;
			// free(quot);
		}
		else
			return (NULL);
	}
	return (var);
}

char	**ft_add_str(char *str, char *input, int *i, char **cp_env, int j, char *flag)
{
	char	*sub;
	char	**var;
	char	*s;
	char	**new;

	sub = ft_substr(input, j, *i - j);
	var = ft_var(sub, cp_env, input[*i], flag);
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
		new = ft_str(input, i, cp_env, flag);
		if (!new)
			return (NULL);
		else
			var[k] = ft_strjoin(var[k], new[0]);
		// free(new);
	}
	return (var);
}

char	**ft_str(char *input, int *i, char **cp_env, char *flag)
{
	char	**str;
	int		j;

	str = NULL;
	if (input[*i] == '"' || input[*i] == '\'')
	{
		str = check_quot(input, i, input[*i], cp_env);
		if (!str || !str[0])
			return (NULL);
	}
	j = *i;
	while (input[*i] && input[*i] != '>' && input[*i] != '<' && input[*i] != '|'
		&& input[*i] != ' ' && input[*i] != '\t' && input[*i] != '\n' && input[*i] != '"' && input[*i] != '\'')
		(*i)++;
	if (j != *i)
	{
		if (str)
		{
			int k = 0;
			while (str[k])
				k++;
			str = ft_add_str(str[k - 1], input, i, cp_env, j, flag);
		}
		else
			str = ft_new_str(input, i, cp_env, j, flag);
	}
	return (str);
}

char	**ft_splitjoin(char	**split1, char **split2)
{
	int	i;
	int	j;
	int	len_split1;
	int	len_split2;
	char	**split3;
	
	i = 0;
	j = 0;
	len_split1 = 0;
	len_split2 = 0;
	while (split1 && split1[len_split1])
		len_split1++;
	while (split2 && split2[len_split2])
		len_split2++;
	split3 = malloc(sizeof(char *) * (len_split1 + len_split2 + 1));
	while (i < len_split1)
	{
		split3[i] = ft_strdup(split1[i]);
		i++;
	}
	while (j < len_split2)
	{
		split3[len_split1 + j] = ft_strdup(split2[j]);
		j++;
	}
	split3[len_split1 + len_split2] = NULL;
	return(split3);
}

t_lexer	*get_str(char *input, int *i, t_lexer *lexer, char **cp_env)
{
	char	**str;
	char	**tmp;
	char	**init_str;
	t_lexer	*new_lex;
	char	*flag;
	int k = 0;
	
	new_lex = lexer;
	while (new_lex)
	{
		flag = new_lex->flag;
		new_lex = new_lex->next;
	}
	
	str = ft_str(input, i, cp_env, flag);
	if (!str)
		return (NULL);
	while (input[*i] == '"' || input[*i] == '\'')
	{
		k = 0;
		tmp = ft_str(input, i, cp_env, lexer->flag);
		while (str[k])
			k++;
		k--;
		init_str = ft_splitjoin(str, tmp);
		// free(str[k]);
		// free(tmp);
		int l = 0;
		while (str[l])
		{
			free(str[l]);
			l++;
		}
		free(str);
		str = init_str;
	}
	k = 0;
	while (str[k])
	{
		add_ch(&lexer, "string", str[k]);
		k++;
	}
	free_str(str, 0);
	return (lexer);
}
