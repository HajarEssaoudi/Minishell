/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:40:23 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/07 16:29:13 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void execute_with_pipe(t_tok *tok, char **env, t_shell *shell)
{
	int fd[2];
	int prev_fd = -1;
	pid_t pid;
	int is_last;

	while (tok)
	{
		is_last = !(tok->pip && tok->pip[0] == '|');
		if (!is_last && pipe(fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid == 0)
		{
			if (tok->heredoc_fd != -1)
			{
				dup2(tok->heredoc_fd, STDIN_FILENO);
				close(tok->heredoc_fd);
			}
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (!is_last)
			{
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}
			execute_redirect(tok, env, shell);
			if (is_built_in(tok->str[0], env))
				execute_built_in(tok, shell, env);
			else
				ft_execve(tok, env);
			exit(EXIT_FAILURE);
		}
		else if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (!is_last)
			{
				close(fd[1]);
				prev_fd = fd[0];
			}
			else
				prev_fd = -1;
		}
		tok = tok->next;
	}
	while (wait(NULL) > 0);
}


void	execute_without_pipe(t_tok *tok, t_shell *shell, char **env)
{
	int saved_stdout;
	int	saved_stdin;

	saved_stdout = -1;
	saved_stdin = -1;
	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	if (tok->heredoc_fd != -1)
	{
		dup2(tok->heredoc_fd, STDIN_FILENO);
		close(tok->heredoc_fd);
	}
	if (tok->redirect && tok->heredoc_fd == -1)
	{
		execute_redirect(tok, env, shell);
	}
	if(is_built_in(tok->str[0], env))
		execute_built_in(tok, shell, env);
	else
		execute_with_execve(tok, env);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

void	execute_cmd(t_tok *tok, t_shell *shell, char **env)
{
	t_tok *tmp = tok;
	while (tmp)
	{
		tmp->heredoc_fd = -1;
		t_rederict *redir = tmp->redirect;
		while (redir)
		{
			if (ft_strcmp(redir->type, "<<") == 0)
				ft_herdoc(tmp, redir->filename, env, shell);
			redir = redir->next;
		}
		tmp = tmp->next;
	}
	tok = check_cmd(tok, env);
	if (!tok)
		return ;
	if (tok->pip && tok->pip[0] == '|')
	{
		execute_with_pipe(tok, env, shell);
	}
	else
	{
		execute_without_pipe(tok, shell, env);
	}
}
