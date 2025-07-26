/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdelhaqmarouan <abdelhaqmarouan@student.42.fr>  #+#  +:+      
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-23 15:23:07 by abdelhaqmarouan   #+#    #+#             */
/*   Updated: 2025-07-23 15:23:07 by abdelhaqmarouan  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	ft_amg(t_lexer *lexer)
{
	t_lexer	*tmp;
	t_lexer	*next;

	tmp = lexer;
	while (tmp)
	{
		if (tmp->ambg && !ft_strcmp(tmp->ambg, "3"))
		{
			next = tmp->next;
			while (next && !ft_strcmp(next->type, "filename"))
			{
				if (!next->ambg)
					next->ambg = ft_strdup("3");
				next = next->next;
			}
		}
		tmp = tmp->next;
	}
}
