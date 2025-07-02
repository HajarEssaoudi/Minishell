/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:19:10 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/01 21:35:59 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_execve(t_tok *tok, char **env)
{
	if (execve(tok->path, tok->str, env) == -1)
	{
		perror("minishell");
		// ft_clear_and_exits
		exit(1);
	}
}

void	execute_with_execve(t_tok *tok, char **env)
{
	pid_t	pid;
	int		status;

	tok = check_cmd(tok, env);
	if (!tok)
		return ; /// a corriger so that check_cmd dont return NULL , mais exits directement
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		// ft_clear_exits
	}
	if (pid == 0)
	{
		ft_execve(tok, env);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}
