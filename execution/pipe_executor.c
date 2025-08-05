/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 00:45:07 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/05 02:19:55 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

extern int	g_flag;

static void	handle_parent_fds(t_tok *tok, int *prev_fd, int fd[2])
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (tok->pip && tok->pip[0] == '|')
	{
		close(fd[1]);
		*prev_fd = fd[0];
	}
	else
		*prev_fd = -1;
}

static void	handle_child_fds(t_tok *tok, int *prev_fd, int fd[2])
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	check_herdoc_fd(tok);
	if (*prev_fd != -1)
	{
		dup2(*prev_fd, STDIN_FILENO);
		close(*prev_fd);
	}
	if (tok->pip && tok->pip[0] == '|')
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
}

void	ft_wait(pid_t last_pid, t_shell *shell)
{
	int		status;
	int		sig;
	pid_t	w_pid;

	w_pid = wait(&status);
	while (w_pid > 0)
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
		else if (w_pid == last_pid && WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		w_pid = wait(&status);
	}
}

void	handle_pipe(t_tok *tok, t_shell *shell, char **env, pid_t *last_pid)
{
	pid_t	pid;
	int		fd[2];
	int		prev_fd;

	prev_fd = -1;
	open_pipe(tok, fd);
	pid = fork();
	if (pid == 0)
	{
		handle_child_fds(tok, &prev_fd, fd);
		execute_cases(tok, shell, env);
		exit(shell->exit_status);
	}
	else if (pid < 0)
		fork_error();
	else
	{
		*last_pid = pid;
		handle_parent_fds(tok, &prev_fd, fd);
	}
}

void	execute_with_pipe(t_tok *tok, char **env, t_shell *shell)
{
	pid_t	pid;
	pid_t	last_pid;
	t_tok	*tmp;
	int		fd[2];
	int		prev_fd;

	g_flag = 1;
	while (tok)
	{
		if (tok->path || tok->redirect)
		{
			handle_pipe(tok, shell, env, &last_pid);
		}
		tmp = tok;
		tok = tok->next;
		tmp->next = NULL;
		free_tok(tmp);
	}
	ft_wait(last_pid, shell);
	g_flag = 0;
}
