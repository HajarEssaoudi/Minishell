/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 00:45:07 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/03 09:00:14 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

extern int	g_flag;

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

void	fork_error(void)
{
	perror("fork");
	if (errno == EACCES)
		exit(EXIT_NO_PERMISSION);
	else if (errno == ENOENT)
		exit(EXIT_NOT_FOUND);
	else
		exit(EXIT_FAILURE);
}

void	execute_with_pipe(t_tok *tok, char **env, t_shell *shell)
{
	int		fd[2];
	pid_t	pid;
	pid_t	last_pid;
	pid_t	w_pid;
	t_tok	*tmp;

	int (status), sig, prev_fd = -1;
	g_flag = 1;
	while (tok)
	{
		if (tok->path || tok->redirect)
		{
			open_pipe(tok, fd);
			pid = fork();
			if (pid == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				handle_child_fds(tok, &prev_fd, fd[1], fd[0]);
				execute_cases(tok, shell, env);
				exit(shell->exit_status);
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
	while ((w_pid = wait(&status)) > 0)
	{
		if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == SIGQUIT)
			{
				ft_putstr_fd("Quit (core dumped)\n", 2);
				shell->exit_status = 131;
			}
			else if (sig == SIGINT)
			{
				write(1, "\n", 1);
				shell->exit_status = 130;
			}
		}
		else if (w_pid == last_pid)
		{
			if (WIFEXITED(status))
				shell->exit_status = WEXITSTATUS(status);
		}
	}
	g_flag = 0;
}
