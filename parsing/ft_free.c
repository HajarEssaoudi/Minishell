/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:20:36 by mabdelha          #+#    #+#             */
/*   Updated: 2025/07/31 08:59:40 by mabdelha         ###   ########.fr       */
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

	if (!lexer)
		return ;
	while (lexer)
	{
		tmp = lexer->next;
		if (lexer->args)
			free(lexer->args);
		if (lexer->type)
			free(lexer->type);
		if (lexer->flag)
			free(lexer->flag);
		if (lexer->ambg)
			free(lexer->ambg);
		free(lexer);
		lexer = tmp;
	}
}

void	free_red(t_rederict *redir)
{
	t_rederict	*tmp_redir;

	while (redir)
	{
		tmp_redir = redir->next;
		if (redir->filename)
			free(redir->filename);
		if (redir->flag)
			free(redir->flag);
		if (redir->type)
			free(redir->type);
		free(redir);
		redir = tmp_redir;
	}
}

void	free_tok(t_tok *tok)
{
	t_tok		*tmp_tok;
	t_rederict	*redir;

	while (tok)
	{
		redir = tok->redirect;
		free_red(redir);
		if (tok->execute)
			free(tok->execute);
		if (tok->path)
			free(tok->path);
		if (tok->pip)
			free(tok->pip);
		if (tok->str)
			free_str(tok->str);
		tmp_tok = tok->next;
		free(tok);
		tok = tmp_tok;
	}
}
