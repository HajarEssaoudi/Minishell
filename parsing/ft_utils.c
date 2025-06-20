/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:06:34 by mabdelha          #+#    #+#             */
/*   Updated: 2025/06/12 18:49:28 by hes-saou         ###   ########.fr       */
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
			tmp = tmp->next;
		tmp->next = token;
	}
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
