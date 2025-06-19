/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:44:31 by mabdelha          #+#    #+#             */
/*   Updated: 2025/06/12 18:50:16 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**check_quot(char *input, int *index, char quot, char **cp_env)
{
	t_quot	*vars;
	char	**result;

	vars = malloc(sizeof(t_quot));
	result = malloc(sizeof(char *) * 2);
	vars->start = *index + 1;
	vars->i = vars->start;
	vars->str = NULL;
	while (input[vars->i] && input[vars->i] != quot)
		vars->i++;
	if (input[vars->i] == quot)
	{
		if (quot == '"')
		{
			vars->sub = ft_substr(input, vars->start, vars->i - vars->start);
			vars->str = *ft_var(vars->sub, cp_env, quot, "0");
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
