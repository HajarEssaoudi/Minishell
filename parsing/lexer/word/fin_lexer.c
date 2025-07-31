/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fin_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:18:45 by mabdelha          #+#    #+#             */
/*   Updated: 2025/07/31 02:46:13 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing.h"

char	*final_quot(char *final, t_split *fin_split)
{
	char	*tmp;

	tmp = NULL;
	if (final)
	{
		tmp = ft_strjoin(final, fin_split->str);
		free(final);
		final = tmp;
	}
	else
	{
		if (final)
			free(final);
		final = ft_strdup(fin_split->str);
	}
	return (final);
}

char	*final_amg(char *amg, char **final_split)
{
	int	i;

	i = 0;
	while (final_split[i])
		i++;
	if (i > 1 || i == 0)
		amg = "3";
	return (amg);
}

char	*handl_fin_split(char *final, t_split *fin_split,
		t_lexer_final *lexer_final)
{
	while (fin_split)
	{
		if (fin_split->quoted)
			final = final_quot(final, fin_split);
		else
		{
			lexer_final->final_split = ft_split_final(fin_split->str);
			if (!fin_split->quoted && !ft_strcmp(fin_split->flag, "2"))
				lexer_final->amg = final_amg(lexer_final->amg,
						lexer_final->final_split);
			if (fin_split->first_space && fin_split->last_space)
				final = final_spaces(final, lexer_final);
			else if (!fin_split->first_space && fin_split->last_space)
				final = fin_last_space(final, lexer_final);
			else if (fin_split->first_space && !fin_split->last_space)
				final = fin_first_space(final, lexer_final);
			else
				final = fin_no_spaces(final, lexer_final);
		}
		fin_split = fin_split->next;
	}
	return (final);
}

void	free_split(t_split *split)
{
	t_split	*tmp;

	while (split)
	{
		tmp = split->next;
		free(split->str);
		free(split);
		split = tmp;
	}
}

t_lexer	*ft_final(t_lexer *lexer, t_split *split)
{
	char			*final;
	t_lexer_final	*lexer_final;
	t_split			*fin_split;

	fin_split = split;
	final = NULL;
	lexer_final = malloc(sizeof(t_lexer_final));
	if (!lexer_final)
		return (NULL);
	lexer_final->lexer = &lexer;
	lexer_final->amg = "0";
	lexer_final->final_split = NULL;
	final = handl_fin_split(final, fin_split, lexer_final);
	if (final)
	{
		add_ch(lexer_final->lexer, "string", final, lexer_final->amg);
		free(final);
	}
	else if (!final && !ft_strcmp(lexer_final->amg, "3"))
		add_ch(lexer_final->lexer, "string", "", lexer_final->amg);
	free(lexer_final);
	free_split(split);
	return (lexer);
}
