/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 10:59:50 by mabdelha          #+#    #+#             */
/*   Updated: 2025/08/07 10:59:52 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing.h"

int	count_final_split(t_lexer_final *lexer_final)
{
	int	i;

	i = 0;
	while (lexer_final->final_split[i])
		i++;
	return (i);
}

void	add_middel_split(t_lexer_final *lexer_final, int j)
{
	int	i;

	i = 1;
	while (lexer_final->final_split[i] && i < j - 1)
	{
		add_ch(lexer_final->lexer, "string", lexer_final->final_split[i],
			lexer_final->amg);
		i++;
	}
}
