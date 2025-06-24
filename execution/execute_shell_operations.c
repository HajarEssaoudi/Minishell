/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_shell_operations.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:16:36 by hes-saou          #+#    #+#             */
/*   Updated: 2025/06/24 17:07:36 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_out(t_tok *tok, char **env, t_shell *shell)
{
	pid_t	pid;
	int		status;
	int		fd;

	pid = fork();
	if (pid == 0)
	{
		fd = open(tok->output[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			close(fd);
			exit(EXIT_FAILURE);
		}
		close(fd);
		if(is_built_in(tok->str[0], env))
			execute_built_in(tok, shell, env);
		else
			execute_execve(tok, env, 1);
	}
	if (pid > 0)
		waitpid(pid, &status, 0);
	else
	{
		perror("fork failed");
		return ;
	}
}

void	ft_in(t_tok *tok, char **env, t_shell *shell)
{
	pid_t	pid;
	int		status;
	int		fd;

	pid = fork();
	if (pid == 0)
	{
		fd = open(tok->input[1], O_RDONLY);
		if (fd < 0)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			close(fd);
			exit(EXIT_FAILURE);
		}
		close(fd);
		if(is_built_in(tok->str[0], env))
			execute_built_in(tok, shell, env);
		else
			execute_execve(tok, env, 1);
	}
	if (pid > 0)
		waitpid(pid, &status, 0);
	else
	{
		perror("fork failed");
		return ;
	}
}

void	execute_with_pipe(t_tok *tok, char **env, t_shell *shell)
{
	int	fd[2];
	int	prev_fd;
	pid_t pid1;

	prev_fd = -1;
	while(tok)
	{
		if (tok->pip && tok->pip[0] == '|')
		{
			if (pipe(fd) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}
		pid1 = fork();
		if (pid1 == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid1 == 0)
		{
			/*if not the first cmd*/
			if (prev_fd != -1)
			{
				dup2(prev_fd, 0);
				close(prev_fd);
			}
			/*not last cmd*/
			if (tok->pip && tok->pip[0] == '|')
			{
				close (fd[0]);
				dup2(fd[1], 1);
				close(fd[1]);
			}
			if(is_built_in(tok->str[0], env))
			{
				execute_built_in(tok, shell, env);
				exit(shell->exit_status);
			}
			else
				execute_execve(tok, env, 0);
		}
		else
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (tok->pip && tok->pip[0] == '|')
			{
				close(fd[1]);
				prev_fd = fd[0];
			}
			else
			{
				if (prev_fd != -1)
					close(prev_fd);
				break;
			}
		}
		tok = tok->next;
	}
	while(wait(NULL) > 0);
}

void	ft_herdoc(t_tok *tok, char **env, t_shell *shell)
{
	char	*line;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return;
	}

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, tok->heredoc[1]) == 0)
			break;
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);

	dup2(pipefd[0], 0);
	close(pipefd[0]);

	if (is_built_in(tok->str[0], env))
		execute_built_in(tok, shell, env);
	else
		execute_execve(tok, env, 1);
}

void	ft_append(t_tok *tok, char **env, t_shell *shell)
{
	pid_t	pid;
	int		status;
	int		fd;

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		return;
	}
	if (pid == 0)
	{
		fd = open(tok->append[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			close(fd);
			exit(EXIT_FAILURE);
		}
		close(fd);
		if (is_built_in(tok->str[0], env))
			execute_built_in(tok, shell, env);
		else
			execute_execve(tok, env, 1);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}
