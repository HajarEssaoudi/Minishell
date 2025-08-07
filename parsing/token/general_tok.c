/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_tok.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:36:46 by mabdelha          #+#    #+#             */
/*   Updated: 2025/08/07 22:11:41 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	add_rederict(t_rederict **rederect, char *type, char *filename,
		char *flag)
{
	t_rederict	*new_rederict;
	t_rederict	*tmp;

	new_rederict = malloc(sizeof(t_rederict));
	if (!new_rederict)
		return ;
	if (filename)
		new_rederict->filename = ft_strdup(filename);
	else
		new_rederict->filename = ft_strdup("");
	new_rederict->type = ft_strdup(type);
	if (flag)
		new_rederict->flag = ft_strdup(flag);
	else
		new_rederict->flag = ft_strdup("0");
	new_rederict->next = NULL;
	tmp = *rederect;
	if (!*rederect)
		*rederect = new_rederict;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_rederict;
	}
}

void	ft_tok_redirect(t_lexer *lexer, char *type, t_tok *tmp)
{
	char	*flag;

	flag = NULL;
	if (!ft_strcmp(lexer->type, "filename"))
	{
		if (!ft_strcmp(lexer->ambg, "3"))
			flag = "1";
		else if (lexer->quot == 0 && ft_strcmp(lexer->ambg, "3"))
			flag = "2";
		if (!ft_strcmp(type, "output"))
			add_rederict(&tmp->redirect, ">", lexer->args, flag);
		else if (!ft_strcmp(type, "input"))
			add_rederict(&tmp->redirect, "<", lexer->args, flag);
		else if (!ft_strcmp(type, "append"))
			add_rederict(&tmp->redirect, ">>", lexer->args, flag);
		else if (!ft_strcmp(type, "heredoc"))
			add_rederict(&tmp->redirect, "<<", lexer->args, flag);
	}
}

void	ft_tok_word_cmd(t_lexer *lexer, t_tok *tmp)
{
	if (!ft_strcmp(lexer->type, "cmd"))
	{
		tmp->path = ft_strdup(lexer->args);
		tmp->str = ft_argv(tmp->str, lexer->args);
	}
	if (!ft_strcmp(lexer->type, "string"))
	{
		tmp->str = ft_argv(tmp->str, lexer->args);
	}
	if (!ft_strcmp(lexer->type, "pip"))
		tmp->pip = ft_strdup("|");
}

t_tok	*ft_token(t_lexer *lexer)
{
	t_tok	*tok;
	t_tok	*tmp;
	char	*type;

	tok = malloc(sizeof(t_tok));
	ft_memset(tok, 0, sizeof(t_tok));
	tmp = tok;
	type = lexer->type;
	while (lexer)
	{
		ft_tok_word_cmd(lexer, tmp);
		ft_tok_redirect(lexer, type, tmp);
		tmp->quot = lexer->quot;
		if (!(ft_strncmp(lexer->type, "pip", ft_strlen("pip"))))
		{
			tmp->next = malloc(sizeof(t_tok));
			ft_memset(tmp->next, 0, sizeof(t_tok));
			tmp = tmp->next;
		}
		type = lexer->type;
		lexer = lexer->next;
	}
	return (tok);
}

t_tok	*get_tok(char *prompt, char **env, int exit_status)
{
	t_tok	*tok;
	t_lexer	*lexer;

	tok = NULL;
	lexer = ft_lexer(prompt, env, exit_status);
	if (lexer)
	{
		ft_type(lexer);
		tok = ft_token(lexer);
	}
	free_lexer(lexer);
	return (tok);
}
