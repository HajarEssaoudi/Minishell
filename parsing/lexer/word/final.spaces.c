/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final.spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdelhaqmarouan <abdelhaqmarouan@student.42.fr>  #+#  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-23 15:13:28 by abdelhaqmarouan   #+#    #+#             */
/*   Updated: 2025-07-23 15:13:28 by abdelhaqmarouan  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing.h"

char	*final_spaces(char *final, t_lexer_final *lexer_final)
{
	int	i;

	i = 0;
	if (final)
	{
		add_ch(lexer_final->lexer, "string", final, lexer_final->amg);
		free(final);
		final = ft_strdup("");
	}
	while (lexer_final->final_split[i])
	{
		add_ch(lexer_final->lexer, "string", lexer_final->final_split[i],
			lexer_final->amg);
		i++;
	}
	free_str(lexer_final->final_split);
	return (final);
}

char	*fin_last_space(char *final, t_lexer_final *lexer_final)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = 1;
	if (final)
	{
		tmp = ft_strjoin(final, lexer_final->final_split[0]);
		add_ch(lexer_final->lexer, "string", tmp, lexer_final->amg);
		free(final);
		free(tmp);
		final = ft_strdup("");
	}
	else if (lexer_final->final_split[0])
		add_ch(lexer_final->lexer, "string", lexer_final->final_split[0],
			lexer_final->amg);
	while (lexer_final->final_split[i])
	{
		add_ch(lexer_final->lexer, "string", lexer_final->final_split[i],
			lexer_final->amg);
		i++;
	}
	free_str(lexer_final->final_split);
	return (final);
}

char	*fin_first_space(char *final, t_lexer_final *lexer_final)
{
	int	j;
	int	i;

	if (final)
	{
		add_ch(lexer_final->lexer, "string", final, lexer_final->amg);
		free(final);
		final = ft_strdup("");
	}
	j = count_final_split(lexer_final);
	i = 0;
	while (lexer_final->final_split[i] && i < j - 1)
	{
		add_ch(lexer_final->lexer, "string", lexer_final->final_split[i],
			lexer_final->amg);
		i++;
	}
	if (j > 0 && lexer_final->final_split[j - 1])
	{
		if (final)
			free(final);
		final = ft_strdup(lexer_final->final_split[j - 1]);
	}
	return (free_str(lexer_final->final_split), final);
}

char	*last_split(char *final, int j, t_lexer_final *lexer_final)
{
	add_middel_split(lexer_final, j);
	if (j > 1 && lexer_final->final_split[j - 1])
	{
		if (final)
		{
			add_ch(lexer_final->lexer, "string", final, lexer_final->amg);
			free(final);
			final = ft_strdup(lexer_final->final_split[j - 1]);
		}
		else
		{
			if (final)
				free(final);
			final = ft_strdup(lexer_final->final_split[j - 1]);
		}
	}
	free_str(lexer_final->final_split);
	return (final);
}

char	*fin_no_spaces(char *final, t_lexer_final *lexer_final)
{
	char	*tmp;
	int		j;

	tmp = NULL;
	if (final && lexer_final->final_split[0])
	{
		tmp = ft_strjoin(final, lexer_final->final_split[0]);
		free(final);
		final = tmp;
	}
	else if (lexer_final->final_split[0])
	{
		if (final)
			free(final);
		final = ft_strdup(lexer_final->final_split[0]);
	}
	j = 0;
	while (lexer_final->final_split[j])
		j++;
	final = last_split(final, j, lexer_final);
	return (final);
}
