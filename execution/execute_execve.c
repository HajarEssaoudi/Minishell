/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:19:10 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/08 00:52:02 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*a ajouter ft_clear exit*/

void	ft_execve(t_tok *tok, char **env)
{
	if (execve(tok->path, tok->str, env) == -1)
	{
		perror("minishell");
		exit(1);
	}
}

void	execute_cases(t_tok *tok, t_shell *shell, char **env)
{
	execute_redirect(tok, env, shell);
	if (is_built_in(tok->str[0], env))
		execute_built_in(tok, shell, env);
	else
		ft_execve(tok, env);
	exit(EXIT_FAILURE);
}
/*a corriger {if (!tok) return; } */
/*add ft_clear_exits so that check_cmd dont return NULL*/
/*mais exits directement*/

void	execute_with_execve(t_tok *tok, char **env)
{
	pid_t	pid;
	int		status;

	tok = check_cmd(tok, env);
	if (!tok)
		return ;
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
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
