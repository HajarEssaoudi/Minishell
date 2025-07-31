/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 01:39:53 by mabdelha          #+#    #+#             */
/*   Updated: 2025/07/30 21:36:29 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing.h"

int	ft_is_quoted(char *input, int *i, char quot)
{
	(*i)++;
	while (input[*i] && input[*i] != quot)
	{
		if (input[*i] == quot && input[*i - 1] == '\\')
			(*i)++;
		else
			(*i)++;
	}
	if (!input[*i])
	{
		printf("Minishell: syntax error: unclosed `%c' quote\n", quot);
		return (-1);
	}
	(*i)++;
	return (0);
}

int	pars_word(char *input, int *i, int *is_quoted)
{
	int		j;
	char	quot;

	j = *i;
	quot = 0;
	while (input[*i] && is_word(input[*i]))
	{
		if (input[*i] == '"' || input[*i] == '\'')
		{
			quot = input[*i];
			*is_quoted = 1;
			if (ft_is_quoted(input, i, quot) == -1)
				return (-1);
		}
		else
			(*i)++;
	}
	return (j);
}

char	*get_flag(t_lexer *lexer)
{
	t_lexer	*tmp;
	char	*flag;

	tmp = lexer;
	flag = NULL;
	while (tmp)
	{
		flag = tmp->flag;
		tmp = tmp->next;
	}
	return (flag);
}

void	herdoc_quot(t_lexer *lexer, int is_quoted)
{
	t_lexer	*prev;
	t_lexer	*last;

	last = lexer;
	prev = NULL;
	while (last->next)
		last = last->next;
	if (last && last->type && !ft_strcmp(last->type, "string"))
	{
		prev = lexer;
		while (prev && prev->next != last)
			prev = prev->next;
		if (prev && prev->type && !ft_strcmp(prev->type, "heredoc"))
			last->quot = is_quoted;
	}
}

t_lexer	*ft_word(t_lexer *lexer, char *input, int *i, char **env)
{
	int		j;
	int		is_quoted;
	char	*sub;
	char	*flag;

	is_quoted = 0;
	j = pars_word(input, i, &is_quoted);
	if (j == -1)
		return (free_lexer(lexer), NULL);
	sub = ft_substr(input, j, *i - j);
	if (!sub)
		return (free_lexer(lexer), NULL);
	flag = get_flag(lexer);
	lexer = get_str(sub, lexer, env, flag);
	if (!lexer)
	{
		free(sub);
		return (free_lexer(lexer), NULL);
	}
	// if (lexer->flag)
	// 	free(lexer->flag);
	herdoc_quot(lexer, is_quoted);
	// lexer->flag = ft_strdup("0");
	free(sub);
	return (lexer);
}
