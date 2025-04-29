/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:55:03 by hes-saou          #+#    #+#             */
/*   Updated: 2025/04/29 16:21:23 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_simple_cmd(t_tok *tok, char **env)
{
	char	**args;

	if (execve(tok->path, tok->str, env) == -1)
	{
		perror("minishell failed");
		exit(EXIT_FAILURE);
	}
}

void	execute_cmd(t_tok *tok, char **env)
{
	// if(is_built_in(tok))
	// 	execute_built_in(tok);
	// else
	execute_simple_cmd(tok, env);
}