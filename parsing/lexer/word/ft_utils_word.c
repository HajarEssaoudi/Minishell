/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdelhaqmarouan <abdelhaqmarouan@student.42.fr>  #+#  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-24 02:20:33 by abdelhaqmarouan   #+#    #+#             */
/*   Updated: 2025-07-24 02:20:33 by abdelhaqmarouan  ###   ########.fr       */
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
