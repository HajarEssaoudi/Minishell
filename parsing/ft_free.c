/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:20:36 by mabdelha          #+#    #+#             */
/*   Updated: 2025/07/16 08:06:34 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_lexer(t_lexer *lexer)
{
	t_lexer	*tmp;

	while (lexer)
	{
		tmp = lexer->next;
		if (lexer->args)
			free(lexer->args);
		if (lexer->type)
			free(lexer->type);
		if (lexer->flag)
			free(lexer->flag);
		free(lexer);
		lexer = tmp;
	}
}

void	free_tok(t_tok *tok)
{
	if (tok->redirect)
	{
		while (tok->redirect)
		{
			if (tok->redirect->filename)
				free(tok->redirect->filename);
			if (tok->redirect->flag)
				free(tok->redirect->flag);
			if (tok->redirect->type)
				free(tok->redirect->type);
			tok->redirect = tok->redirect->next;
		}
	}
	if(tok->execute)
		free(tok->execute);
	if (tok->path)
		free(tok->path);
	if (tok->pip)
		free(tok->pip);
	if (tok->str)
		free_str(tok->str);
	free(tok);
}
