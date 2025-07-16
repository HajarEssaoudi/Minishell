/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:44:31 by mabdelha          #+#    #+#             */
/*   Updated: 2025/07/16 10:39:39 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**check_quot(char *input, int *index, char quot, char **cp_env, t_lexer *lexer)
{
	t_quot	*vars;
	char	**result;

	vars = malloc(sizeof(t_quot));
	result = malloc(sizeof(char *) * 2);
	vars->start = *index + 1;
	vars->i = vars->start;
	vars->str = NULL;
	lexer->quot = 0;
	while (input[vars->i] && (input[vars->i] != quot || (input[vars->i] == quot && input[vars->i - 1] == '\\')))
		vars->i++;
	if (input[vars->i] == quot)
	{
		if (quot == '"')
		{
			vars->sub = ft_substr(input, vars->start, vars->i - vars->start);
			vars->str = *ft_var(vars->sub, cp_env, quot, 0, lexer);
			free(vars->sub);
		}
		else
			vars->str = ft_substr(input, vars->start, vars->i - vars->start);
		*index = vars->i + 1;
	}
	else
	{
		printf("Minishell: syntax error: unclosed `%c' quote\n", quot);
		return (NULL);
	}
	result[0] = vars->str;
	result[1] = NULL;
	free(vars);
	return (result);
}
