/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:06:34 by mabdelha          #+#    #+#             */
/*   Updated: 2025/07/20 19:28:09 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
	token->ambg = ambg;
	token->quot = (*lexer)->quot;
	if (!*lexer || !(*lexer)->type)
	{
		if (*lexer)
			free(*lexer);
		*lexer = token;
	}
	else
		add_lexer(*lexer, token);
}

char	*ft_special_caract(char *result, char *var)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strjoin(result, var);
	free(var);
	free(result);
	return (tmp);
}
