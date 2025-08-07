/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 10:58:45 by mabdelha          #+#    #+#             */
/*   Updated: 2025/08/07 10:58:49 by mabdelha         ###   ########.fr       */
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
