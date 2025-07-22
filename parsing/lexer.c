/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:04:37 by mabdelha          #+#    #+#             */
/*   Updated: 2025/07/22 20:45:59 by mabdelha         ###   ########.fr       */
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
		lexer = ft_word(lexer, input, i, env);
		if (!lexer)
		{
			free_lexer(lexer);
			return (NULL);
		}
	}
	return (lexer);
}

t_lexer *init_lexer(t_lexer *lexer, int exit_status)
{
	lexer = malloc(sizeof(t_lexer));
	lexer->args = NULL;
	lexer->flag = NULL;
	lexer->next = NULL;
	lexer->type = NULL;
	lexer->ambg = NULL;
	lexer->quot = 0;
	lexer->exit_status = exit_status;
	return (lexer);
}

t_lexer *ft_lexer(char *input, char **env, int exit_status)
{
	int i;
	t_lexer *lexer;

	i = 0;
	lexer = init_lexer(lexer, exit_status);
	while (input[i])
	{
		lexer->exit_status = exit_status;
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
