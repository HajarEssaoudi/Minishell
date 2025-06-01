/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-31 10:20:36 by mabdelha          #+#    #+#             */
/*   Updated: 2025-05-31 10:20:36 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		free(lexer);
		lexer = tmp;
	}
}
