/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 00:45:07 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/31 14:17:35 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	handle_parent_fds(t_tok *tok, int *prev_fd, int fd1, int fd0)
{

	if (*prev_fd != -1)
		close(*prev_fd);
	if (tok->pip && tok->pip[0] == '|')
	{
		close(fd1);
		*prev_fd = fd0;
	}
	else
		*prev_fd = -1;
	
}

static void	handle_child_fds(t_tok *tok, int *prev_fd, int fd1, int fd0)
{
	check_herdoc_fd(tok);
	if (*prev_fd != -1)
	{
		dup2(*prev_fd, STDIN_FILENO);
		close(*prev_fd);
	}
	if (tok->pip && tok->pip[0] == '|')
	{
		close(fd0);
		dup2(fd1, STDOUT_FILENO);
		close(fd1);
	}
}

static void	wait_for_children(pid_t last_pid, t_shell *shell)
{
	int		status;
	pid_t	w_pid;

	while (1)
	{
		w_pid = wait(&status);
		if (w_pid <= 0)
			break ;
		if (w_pid == last_pid && WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
	}
}

void	execute_with_pipe(t_tok *tok, char **env, t_shell *shell)
{
	int		fd[2];
	int		prev_fd;
	pid_t	pid;
	pid_t	last_pid;
	t_tok	*tmp;

	prev_fd = -1;
	while (tok)
	{
		if (tok->path || tok->redirect)
		{
			open_pipe(tok, fd);
			pid = fork();
			if (pid == 0)
			{
				handle_child_fds(tok, &prev_fd, fd[1], fd[0]);
				execute_cases(tok, shell, env);
			}
			else if (pid < 0)
				fork_error();
			else
			{
				last_pid = pid;
				handle_parent_fds(tok, &prev_fd, fd[1], fd[0]);
			}
		}
		tmp = tok;
		tok = tok->next;
		tmp->next = NULL;
		free_tok(tmp);
	}
	wait_for_children(last_pid, shell);
}
