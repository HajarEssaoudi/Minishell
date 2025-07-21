/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:04:37 by mabdelha          #+#    #+#             */
/*   Updated: 2025/07/20 16:40:33 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void ft_ambiguous(t_lexer *tmp)
{
	while (tmp)
	{
		if (tmp->flag)
			free(tmp->flag);
		if (!ft_strcmp(tmp->type, "heredoc"))
			tmp->flag = ft_strdup("1");
		else if (!ft_strcmp(tmp->type, "output"))
			tmp->flag = ft_strdup("2");
		else if (!ft_strcmp(tmp->type, "input"))
			tmp->flag = ft_strdup("2");
		else if (!ft_strcmp(tmp->type, "append"))
			tmp->flag = ft_strdup("2");
		else
			tmp->flag = ft_strdup("0");
		tmp = tmp->next;
	}
}

t_lexer *ft_get_lexer(char *input, t_lexer *lexer, int *i, char **env)
{
	t_lexer *tmp;
	if (input[*i] == '|' || input[*i] == '>' || input[*i] == '<')
	{
		lexer = ft_operator(input, i, lexer);
		if (!lexer)
		{
			free_lexer(lexer);
			return (NULL);
		}
		tmp = lexer;
		ft_ambiguous(tmp);
	}
	else if (input[*i])
	{
		int j = *i;
		char quot;
		int is_quoted = 0;
		while (input[*i] && input[*i] != '>' && input[*i] != '<' && input[*i] != '|'
		&& input[*i] != ' ' && input[*i] != '\t' && input[*i] != '\n')
		{
			if (input[*i] == '"' || input[*i] == '\'')
			{
				quot = input[*i];
				is_quoted = 1;
				(*i)++;
				// j = *i;
				while (input[*i] && input[*i] != quot)
					(*i)++;
				if (!input[*i])
				{
					printf("Minishell: syntax error: unclosed `%c' quote\n", quot);
					return NULL;
				}
				(*i)++;
			}
			else
				(*i)++;
		}
		char *sub = ft_substr(input, j, *i - j);
		// printf("sub => %s\n", sub);
		t_lexer *tmp = lexer;
		char *flag = NULL;
		while (tmp)
		{
			flag = tmp->flag;
			tmp = tmp->next;
		}
		lexer = get_str(sub, lexer, env, flag);
		if (!lexer)
		{
			free_lexer(lexer);
			return (NULL);
		}
		if (lexer->flag)
			free(lexer->flag);
		t_lexer *last = lexer;
		while (last->next)
			last = last->next;
		if (last && last->type && !ft_strcmp(last->type, "string")) {
			t_lexer *prev = lexer;
			while (prev && prev->next != last)
				prev = prev->next;
			if (prev && prev->type && !ft_strcmp(prev->type, "heredoc"))
				last->quot = is_quoted;
		}
		lexer->flag = ft_strdup("0");
	}
	return (lexer);
}

t_lexer *ft_lexer(char *input, char **env)
{
	int i;
	t_lexer *lexer;

	i = 0;
	lexer = malloc(sizeof(t_lexer));
	lexer->args = NULL;
	lexer->flag = NULL;
	lexer->next = NULL;
	lexer->type = NULL;
	lexer->ambg = NULL;
	lexer->quot = 0;

	while (input[i])
	{
		i = skip_space_tab_newline(input, i);
		if (!ft_strlen(input) && !input[i])
			return (NULL);
		else
		{
			lexer = ft_get_lexer(input, lexer, &i, env);
			if (!lexer)
				return (NULL);
		}
	}
	return (lexer);
}
