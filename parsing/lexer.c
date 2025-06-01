/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diviser_promt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-31 19:04:37 by mabdelha          #+#    #+#             */
/*   Updated: 2025-05-31 19:04:37 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*ft_get_lexer(char *input, t_lexer *lexer, int *i, char **env)
{
	if (input[*i] == '|' || input[*i] == '>' || input[*i] == '<')
	{
		lexer = ft_operator(input, i, lexer);
		if (!lexer)
		{
			free_lexer(lexer);
			return (NULL);
		}
	}
	else if (input[*i])
	{
		lexer = get_str(input, i, lexer, env);
		if (!lexer)
		{
			free_lexer(lexer);
			return (NULL);
		}
	}
	return (lexer);
}

t_lexer	*ft_lexer(char *input, char **env)
{
	int		i;
	t_lexer	*lexer;

	i = 0;
	lexer = NULL;
	while (input[i])
	{
		i = skip_space_tab_newline(input, i);
		if (!strlen(input) && !input[i])
			return (NULL);
		else
		{
			lexer = ft_get_lexer(input, lexer, &i, env);
			if (!lexer)
				return (NULL);
		}
	}
	return (lexer);
}
