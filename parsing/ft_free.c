/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:20:36 by mabdelha          #+#    #+#             */
/*   Updated: 2025/07/13 02:23:59 by mabdelha         ###   ########.fr       */
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
	if(tok->append)
		free_str(tok->append);
	if(tok->execute)
		free(tok->execute);
	if(tok->heredoc)
		free_str(tok->heredoc);
	if (tok->input)
		free_str(tok->input);
	if (tok->output)
		free_str(tok->output);
	if (tok->path)
		free(tok->path);
	if (tok->pip)
		free(tok->pip);
	if (tok->str)
		free_str(tok->str);
	free(tok);
}
