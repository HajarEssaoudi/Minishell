/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 00:45:07 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/06 01:56:06 by root             ###   ########.fr       */
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

void	handle_pipe(t_clean *clean, pid_t *last_pid, int *prev_fd)
{
	pid_t	pid;
	int		fd[2];

	open_pipe(clean->tok, fd);
	pid = fork();
	if (pid == 0)
	{
		handle_child_fds(clean->tok, prev_fd, fd);
		execute_cases(clean->tok, clean->shell, clean->env);
		exit(clean->shell->exit_status);
	}
	else if (pid < 0)
		fork_error();
	else
	{
		*last_pid = pid;
		handle_parent_fds(clean->tok, prev_fd, fd);
	}
}

void	execute_with_pipe(t_tok *tok, char **env, t_shell *shell)
{
	pid_t	last_pid;
	int		prev_fd;
	t_clean	clean;
	t_tok	*next;

	g_flag = 1;
	prev_fd = -1;
	ft_memset(&clean, 0, sizeof(t_clean));
	clean.env = env;
	clean.tok = tok;
	clean.shell = shell;
	while (tok)
	{
		next = tok->next;
		tok->next = NULL;
		clean.tok = tok;
		if (tok->path || tok->redirect)
			handle_pipe(&clean, &last_pid, &prev_fd);
		free_tok(tok);
		tok = next;
	}
	ft_wait(last_pid, shell);
	g_flag = 0;
}
