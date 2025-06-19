/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:04:37 by mabdelha          #+#    #+#             */
/*   Updated: 2025/06/12 18:49:46 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
		else if (!ft_strcmp(lexer->args, "<<"))
			lexer->flag = ft_strdup("1");
		else
			lexer->flag = ft_strdup("2");
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
		if (!ft_strlen(input) && !input[i])
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
