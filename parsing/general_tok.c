/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_tok.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:36:46 by mabdelha          #+#    #+#             */
/*   Updated: 2025/06/14 23:40:32 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	add_rederict(t_rederict **rederect, char *type, char *filename)
{
	t_rederict	*new_rederict;
	t_rederict	*tmp;

	new_rederict = malloc(sizeof(t_rederict));
	new_rederict->filename = ft_strdup(filename);
	new_rederict->type = ft_strdup(type);
	new_rederict->next = NULL;
	tmp = rederect;
	if (!*rederect)
		rederect = new_rederict;
	else
	{
		while (tmp)
			tmp = tmp->next;
		tmp->next = new_rederict;
	}
}

void	ft_tok_redirect(t_lexer *lexer, char *type, t_tok *tmp)
{
	if (!(ft_strncmp(lexer->type, "filename", ft_strlen("filename"))))
	{
		if (!(ft_strncmp(type, "output", ft_strlen("output"))))
			tmp->output = ft_red(tmp->output, lexer->args);
		else if (!(ft_strncmp(type, "input", ft_strlen("input"))))
			tmp->input = ft_red(tmp->input, lexer->args);
		else if (!(ft_strncmp(type, "append", ft_strlen("append"))))
			tmp->append = ft_red(tmp->append, lexer->args);
		else if (!(ft_strncmp(type, "heredoc", ft_strlen("heredoc"))))
			tmp->heredoc = ft_red(tmp->heredoc, lexer->args);
	}
	if (!(ft_strncmp(lexer->type, "output", ft_strlen("output"))))
		tmp->output = ft_red(tmp->output, lexer->args);
	if (!(ft_strncmp(lexer->type, "input", ft_strlen("input"))))
		tmp->input = ft_red(tmp->input, lexer->args);
	if (!(ft_strncmp(lexer->type, "append", ft_strlen("append"))))
		tmp->append = ft_red(tmp->append, lexer->args);
	if (!(ft_strncmp(lexer->type, "heredoc", ft_strlen("heredoc"))))
		tmp->heredoc = ft_red(tmp->heredoc, lexer->args);
}

void	ft_tok_word_cmd(t_lexer *lexer, char *type, t_tok *tmp)
{
	if (!(ft_strncmp(lexer->type, "execute", ft_strlen("execute"))))
	{
		tmp->execute = ft_strdup(lexer->args);
	}
	if (!(ft_strncmp(lexer->type, "cmd", ft_strlen("cmd"))))
	{
		tmp->path = ft_strdup(lexer->args);
		tmp->str = ft_argv(tmp->str, lexer->args);
	}
	if (!(ft_strncmp(lexer->type, "string", ft_strlen("string"))))
	{
		tmp->str = ft_argv(tmp->str, lexer->args);
	}
	if (!(ft_strncmp(lexer->type, "pip", ft_strlen("pip"))))
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
		ft_tok_word_cmd(lexer, type, tmp);
		ft_tok_redirect(lexer, type, tmp);
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

t_tok	*get_tok(char *prompt, char **env)
{
	t_tok	*tok;
	t_lexer	*lexer;

	tok = NULL;
	lexer = ft_lexer(prompt, env);
	if (lexer)
	{
		ft_type(lexer);
		tok = ft_token(lexer);
	}
	free_lexer(lexer);
	return (tok);
}