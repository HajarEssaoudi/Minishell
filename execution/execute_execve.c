/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:19:10 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/14 19:05:06 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "execution.h"

extern	int g_flag;

/*a ajouter ft_clear exit*/

void	ft_execve(char *path,char **str, char **env, t_shell *shell)
{
	if (execve(path, str, env) == -1)
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
}

void	execute_cases(t_tok *tok, t_shell *shell, char **env)
{
	execute_redirect(tok, env, shell);
	if (is_built_in(tok->str[0], env))
		execute_built_in(tok, shell, env);
	else
	{
		if (tok->execute)
			ft_execve(tok->execute, NULL, env, shell);
		else if (tok->path)
			ft_execve(tok->path, tok->str, env, shell);
	}
	shell->exit_status = EXIT_FAILURE;
	exit(shell->exit_status);
}
/*a corriger {if (!tok) return; } */
/*add ft_clear_exits so that check_cmd dont return NULL*/
/*mais exits directement*/

void	execute_with_execve(t_tok *tok, t_shell *shell ,char **env)
{
	pid_t	pid;
	int		status;
	int		sig;

	g_flag = 1;
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		tok = check_cmd(tok, env);
		if (!tok)
		{
			exit(EXIT_NOT_FOUND);
		}
		if (tok->execute)
			ft_execve(tok->execute, NULL, env, shell);
		else if (tok->path)
			ft_execve(tok->path, tok->str, env, shell);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == SIGQUIT)
				ft_printf(2, "Quit (core dumped)\n");
			else if (sig == SIGINT)
				printf("\n");
		}
		else if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
	}
	g_flag = 0;
}
