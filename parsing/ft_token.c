/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:47:09 by hes-saou          #+#    #+#             */
/*   Updated: 2025/04/29 16:47:20 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_red(char **argv, char *arg)
{
	int		j;
	char	**argv2;
	int		i;

	j = 0;
	while (argv && argv[j])
		j++;
	argv2 = malloc(sizeof(char *) * (j + 2));
	i = 0;
	while (argv && argv[i])
	{
		argv2[i] = ft_strdup(argv[i]);
		i++;
	}
	argv2[i] = ft_strdup(arg);
	argv2[i + 1] = NULL;
	if (argv)
		free_str(argv);
	return (argv2);
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
