/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:06:34 by mabdelha          #+#    #+#             */
/*   Updated: 2025/08/07 16:59:22 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	is_word(char c)
{
	if (c != ' ' && c != '\t' && c != '\n' && c != '|' && c != '<' && c != '>')
		return (1);
	return (0);
}

int	skip_space_tab_newline(char *str, int i)
{
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	return (i);
}

void	add_lexer(t_lexer *lexer, t_lexer *token)
{
	t_lexer	*tmp;

	tmp = lexer;
	while (tmp->next)
	{
		if (!tmp->quot && !tmp->next->next)
			token->quot = tmp->quot;
		tmp = tmp->next;
	}
	tmp->next = token;
}

void	add_ch(t_lexer **lexer, char *type, char *input, char *ambg)
{
	t_lexer	*token;

	token = malloc(sizeof(t_lexer));
	token->args = ft_strdup(input);
	token->type = ft_strdup(type);
	token->next = NULL;
	token->flag = NULL;
	token->ambg = ft_strdup(ambg);
	token->quot = (*lexer)->quot;
	if (!*lexer)
		*lexer = token;
	else
		add_lexer(*lexer, token);
}
