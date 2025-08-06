/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:19:10 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/06 00:51:03 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

extern int	g_flag;

static void	child_process(t_tok *tok, t_shell *shell, char **env)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	tok = check_cmd(tok, shell, env);
	if (!tok)
		tok_error_handling(shell, env);
	ft_execve(tok, env);
}

static void	parent_process(pid_t pid, t_shell *shell)
{
	int	status;
	int	sig;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
		{
			ft_printf(2, "Quit (core dumped)\n");
			shell->exit_status = 131;
		}
		else if (sig == SIGINT)
		{
			write(1, "\n", 1);
			shell->exit_status = 130;
		}
	}
	else if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
}

void	execute_with_execve(t_tok *tok, t_shell *shell, char **env)
{
	pid_t	pid;

	g_flag = 1;
	pid = fork();
	if (pid < 0)
		perror("fork");
	if (pid == 0)
		child_process(tok, shell, env);
	else
		parent_process(pid, shell);
	g_flag = 0;
}
