/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 00:45:07 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/28 06:24:01 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	open_pipe(t_tok *tok, int *fd)
{
	if (tok->pip && tok->pip[0] == '|' && pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

static void	check_herdoc_fd(t_tok *tok)
{
	if (tok->heredoc_fd != -1)
	{
		dup2(tok->heredoc_fd, STDIN_FILENO);
		close(tok->heredoc_fd);
	}
}

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

void	execute_with_pipe(t_tok *tok, char **env, t_shell *shell)
{
	int		fd[2];
	int		prev_fd;
	pid_t	pid;
	pid_t	last_pid = -1;
	int		status;
	pid_t	w_pid;

	prev_fd = -1;
	while (tok)
	{
		open_pipe(tok, fd);
		pid = fork();
		if (pid == 0)
		{
			handle_child_fds(tok, &prev_fd, fd[1], fd[0]);
			execute_cases(tok, shell, env);
		}
		else if (pid < 0)
		{
			perror("fork");
			if (errno == EACCES)
				exit(EXIT_NO_PERMISSION);
			else if (errno == ENOENT)
				exit(EXIT_NOT_FOUND);
			else
				exit(EXIT_FAILURE);
		}
		else
		{
			last_pid = pid;
			handle_parent_fds(tok, &prev_fd, fd[1], fd[0]);
			t_tok *tmp = tok;
			tok = tok->next;
			tmp->next = NULL;
			free_tok(tmp);
		}
		// tok = tok->next;
	}
	while ((w_pid = wait(&status)) > 0)
	{
		if (w_pid == last_pid)
		{
			if (WIFEXITED(status))
				shell->exit_status = WEXITSTATUS(status);
		}
	}
}

