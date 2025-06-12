/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 23:30:19 by mabdelha          #+#    #+#             */
/*   Updated: 2025/06/12 18:49:42 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_lexer	*handle_redirect_output(char *input, int *i, t_lexer *lexer)
{
	if (!check_redirect1(input))
	{
		add_ch(&lexer, "output", ">");
		(*i)++;
	}
	else
		return (NULL);
	return (lexer);
}

t_lexer	*handle_redirect_input(char *input, int *i, t_lexer *lexer)
{
	if (!check_redirect1(input))
	{
		add_ch(&lexer, "input", "<");
		(*i)++;
	}
	else
		return (NULL);
	return (lexer);
}

t_lexer	*handle_redirect_append(char *input, int *i, t_lexer *lexer)
{
	if (!check_redirect2(input))
	{
		add_ch(&lexer, "append", ">>");
		(*i)++;
	}
	else
		return (NULL);
	return (lexer);
}

t_lexer	*handle_redirect_heredoc(char *input, int *i, t_lexer *lexer)
{
	if (!check_redirect2(input))
	{
		add_ch(&lexer, "heredoc", "<<");
		(*i)++;
	}
	else
		return (NULL);
	return (lexer);
}

t_lexer	*ft_operator(char *input, int *i, t_lexer *lexer)
{
	if (input[*i] == '|')
		lexer = handle_pip(input, i, lexer);
	else if (input[*i] == '>' && input[*i + 1] != '>')
		lexer = handle_redirect_output(input, i, lexer);
	else if (input[*i] == '<' && input[*i + 1] != '<')
		lexer = handle_redirect_input(input, i, lexer);
	else if (input[*i] == '>' && input[*i + 1] == '>')
		lexer = handle_redirect_append(input, i, lexer);
	else if (input[*i] == '<' && input[*i + 1] == '<')
		lexer = handle_redirect_heredoc(input, i, lexer);
	else if (!lexer)
	{
		return (NULL);
	}
	return (lexer);
}
