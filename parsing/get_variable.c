/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 00:11:02 by mabdelha          #+#    #+#             */
/*   Updated: 2025/07/13 09:24:38 by mabdelha         ###   ########.fr       */
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

static char	*handle_normal_char(char *result, char c, char quot)
{
	char	tmp_char[2];
	char	*tmp_result;
	char	*sub;
	int		i;

	i = 0;
	while(result[i])
	{
		if (result[i] == '\\' && c == quot)
		{
			sub = ft_substr(result, 0, i - 0);
			free(result);
			result = sub;
		}
		i++;
	}
	tmp_char[0] = c;
	tmp_char[1] = '\0';
	tmp_result = ft_strjoin(result, tmp_char);
	free(result);
	return (tmp_result);
}


char	**ft_splitIFS(char *str, char *IFS)
{
	int	i;
	int	j;
	int	k;
	char	**new;

	i = 0;
	j = 0;
	k = 0;
	new = malloc (sizeof(char *) * (ft_strlen(str) + 2));
	while (str[i])
	{
		if (ft_strchr(IFS, str[i]))
		{
			new[k++] = ft_substr(str, j, i - j);
			j = i + 1;
			if (new[j])
				new[k++] = ft_strdup("");
		}
		i++;
	}
	if (i > j)
		new[k++] = ft_substr(str, j, i - j);
	else if (str[i - 1] && ft_strchr(IFS, str[i - 1]))
		new[k++] = ft_strdup("");
	new[k] = NULL;
	return (new);
}

char	**ft_var(char *str, char **cp_env, char input, char *flag, t_lexer *lexer)
{
	int		i;
	char	*result;
	char	**split;
	char	*IFS;
	char	**new_split;
	t_lexer	*new_lexer;
	char *new;
	int	k;

	// printf("%s\n", str);

	i = 0;
	k = 0;
	IFS = get_env_var(cp_env, "IFS");
	result = ft_strdup("");
	new_lexer = lexer;
	// result[0] = '\0';
	while (str[i])
	{
		if (str[i] == '~' && (i == 0 || (str[i + 1] == ' ' || str[i + 1] == '\t' || str[i + 1] == '\n' )) && (str[i + 1] == '/'
				|| str[i + 1] == '\0' || (str[i + 1] == ' ' || str[i + 1] == '\t' || str[i + 1] == '\n' )) && (input != '"'
				&& input != '\''))
		{
			printf("%c\n", input);
			result = handle_tilde(result, cp_env, &i);
		}
		if (str[i] == '$' && (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
		{
			k = i;
			result = ft_dollar(str, cp_env, result, &i, flag);
			// printf("result => %s\n", result);
			// printf("dollar => %s\n", result);
		}
		else if (str[i] == '$' && ft_isdigit(str[i + 1]))
			result = handle_normal_char(result, str[i += 2], input);
		else
			result = handle_normal_char(result, str[i++], input);
	}
	// printf("result => %s\n", result);
	if (input != '"' && (ft_strcmp(lexer->args, "export" ) || (!ft_strcmp(lexer->args, "export") && str[k - 1] != '='))	)
	{
		if (IFS)
			split = ft_splitIFS(result, IFS);
		else
			split = ft_split(result, ' ');
		// if (!split || !split[0])
		// {
		// 	split = malloc(sizeof(char *) * 2);
		// 	// if (result[0] == ' ')
		// 	// 	split[0] = ft_strdup(" ");
		// 	// else
		// 	split[0] = ft_strdup("");
		// 	split[1] = NULL;
		// }
		int k = 0;
		while (result[k])
			k++;
		if(result[k - 1] == ' ' && split[0])
		{
			k = 0;
			while (split[k])
				k++;
			new_split = malloc(sizeof(char *) * (k + 2));
			k = 0;
			while (split[k])
			{
				new_split[k] = split[k];
				k++;
			}
			new_split[k] = ft_strdup("");
			new_split[k + 1] = NULL;
			free(split);
			split = new_split;
		}
		free(result);
	}
	else
	{		
		split = malloc(sizeof(char *) * 2);
		split[0] = result;
		split[1] = NULL;
		// free(result);
	}
	// printf("%s\n", flag);
	if ((!split || !split[0] || split[1]) && (flag && flag[0] == '2'))
	{
		// while (new_lexer->next)
		// {
		// 	printf("%s => %s\n", lexer->args, lexer->flag);
		// 	new_lexer = new_lexer->next;
		// }
		// if (lexer->flag)
		// 	free(lexer->flag);
		lexer->ambg = ft_strdup("3");
		// printf ("minishell %s: ambiguous redirect\n", cv_var(str, &k));
		// free_str(split);
		// return (NULL);
	}
	return (split);
}
