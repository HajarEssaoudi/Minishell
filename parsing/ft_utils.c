/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:06:34 by mabdelha          #+#    #+#             */
/*   Updated: 2025/07/13 09:50:15 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	skip_space_tab_newline(char *str, int i)
{
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	return (i);
}

void	add_ch(t_lexer **lexer, char *type, char *input)
{
	t_lexer	*token;
	t_lexer	*tmp;

	token = malloc(sizeof(t_lexer));
	token->args = ft_strdup(input);
	token->type = ft_strdup(type);
	token->next = NULL;
	token->flag = NULL;
	if (!*lexer || !(*lexer)->type)
	{
		if (*lexer)
			free(*lexer);
		*lexer = token;
	}
	else
	{
		tmp = *lexer;
		while (tmp->next)
		{
			if (!ft_strcmp(tmp->ambg, "3"))
				token->ambg = tmp->ambg;
			tmp = tmp->next;
		}
		tmp->next = token;
	}
}

char	*ft_special_caract(char *result, char *var)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strjoin(result, var);
	// printf("var => %s\n", var);
	// printf("tmp => %s\n", tmp);
	free(var);
	free(result);
	return (tmp);
}
