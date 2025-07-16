/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_tok.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:36:46 by mabdelha          #+#    #+#             */
/*   Updated: 2025/07/16 13:00:35 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	add_rederict(t_rederict **rederect, char *type, char *filename, char *flag)
{
	t_rederict	*new_rederict;
	t_rederict	*tmp;

	new_rederict = malloc(sizeof(t_rederict));
	if (filename)
		new_rederict->filename = ft_strdup(filename);
	else
		new_rederict->filename = ft_strdup("");
	new_rederict->type = ft_strdup(type);
	// printf("flag %s\n", flag);
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
		// printf("hhh => %s\n", tmp->type);
	}
}

void	ft_tok_redirect(t_lexer *lexer, char *type, t_tok *tmp)
{
	char *flag = NULL;
	// printf("lexer->ambg => %s\n", lexer->ambg);
	if (!(ft_strncmp(lexer->type, "filename", ft_strlen("filename"))))
	{
		if (!ft_strcmp(lexer->ambg, "3"))
			flag = "1";
		// printf("lexer->ambg2 => %s\n", lexer->ambg);
		if (!(ft_strncmp(type, "output", ft_strlen("output"))))
			add_rederict(&tmp->redirect, ">", lexer->args, flag);
		else if (!(ft_strncmp(type, "input", ft_strlen("input"))))
			add_rederict(&tmp->redirect, "<", lexer->args, flag);
		else if (!(ft_strncmp(type, "append", ft_strlen("append"))))
			add_rederict(&tmp->redirect, ">>", lexer->args, flag);
		else if (!(ft_strncmp(type, "heredoc", ft_strlen("heredoc"))))
			add_rederict(&tmp->redirect, "<<", lexer->args, NULL);
	}
	// if (!(ft_strncmp(lexer->type, "output", ft_strlen("output"))))
	// 	tmp->output = ft_red(tmp->output, lexer->args);
	// if (!(ft_strncmp(lexer->type, "input", ft_strlen("input"))))
	// 	tmp->input = ft_red(tmp->input, lexer->args);
	// if (!(ft_strncmp(lexer->type, "append", ft_strlen("append"))))
	// 	tmp->append = ft_red(tmp->append, lexer->args);
	// if (!(ft_strncmp(lexer->type, "heredoc", ft_strlen("heredoc"))))
	// 	tmp->heredoc = ft_red(tmp->heredoc, lexer->args);
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

void	ft_amg(t_lexer *lexer)
{
	t_lexer	*tmp;
	t_lexer	*next;
	
	tmp = lexer;
	while(tmp)
	{
		if (tmp->ambg && !ft_strcmp(tmp->ambg, "3"))
		{
			next = tmp->next;
			while(next && !ft_strcmp(next->type, "filename"))
			{
				if (!next->ambg)
					next->ambg = ft_strdup("3");
				next = next->next;
			}
		}
		tmp = tmp->next;
	}
}

void print_lexer(t_lexer *lexer)
{
    while (lexer != NULL)
    {
        printf("flag: %s\n", lexer->flag ? lexer->flag : "NULL");
        printf("args: %s\n", lexer->args ? lexer->args : "NULL");
        printf("type: %s\n", lexer->type ? lexer->type : "NULL");
        printf("ambg: %s\n", lexer->ambg ? lexer->ambg : "NULL");
        printf("quot: %d\n", lexer->quot);
        printf("-----------------\n");
        lexer = lexer->next;
    }
}

t_tok	*get_tok(char *prompt, char **env)
{
	t_tok	*tok;
	t_lexer	*lexer;

	tok = NULL;
	lexer = ft_lexer(prompt, env);
	// print_lexer(lexer);
	if (lexer)
	{
		ft_type(lexer);
		ft_amg(lexer);
		tok = ft_token(lexer);
	}
	free_lexer(lexer);
	return (tok);
}
