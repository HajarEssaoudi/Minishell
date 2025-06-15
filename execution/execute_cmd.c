/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:57:59 by hes-saou          #+#    #+#             */
/*   Updated: 2025/06/15 16:42:46 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	execute_cmd(t_tok *tok, char **env, int fd, t_shell *shell)
{
	if (tok->execute)
		execute_executable(tok, env);
	else if(is_built_in(tok->str[0], env))
		execute_built_in(tok, shell, env);
	else
		execute_external_cmd(tok, env, fd);
}

void	 execute_executable(t_tok *tok, char **env)
{
	char	**args;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(tok->execute, tok->str, env) == -1)
		{
			perror("minishell failed");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
	{
		perror("fork failed");
		return ;
	}
}

void	execute_built_in(t_tok *tok, t_shell *shell, char **env)
{
	if (ft_strcmp("cd", tok->str[0]) == 0)
		execute_cd(tok, shell);
	else if (ft_strcmp("pwd", tok->str[0]) == 0)
		execute_pwd(shell);
	else if (ft_strcmp("echo", tok->str[0]) == 0)
		execute_echo(tok);
	else if (ft_strcmp("env", tok->str[0]) == 0)
		execute_env(env);
	else if (ft_strcmp("exit", tok->str[0]) == 0)
		execute_exit(tok, shell);
	else if (ft_strcmp("unset", tok->str[0]) == 0)
		execute_unset(tok, shell);
	else if (ft_strcmp("export", tok->str[0]) == 0)
		execute_export(tok, shell);
}

void	execute_with_pipe(t_tok *tok, char **env)
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
		if (pid1 == 0)
		{
			/*if not the first cmd*/
			if (prev_fd != -1)
			{
				dup2(prev_fd, 0);
				close(prev_fd);
			}
			if (tok->pip && tok->pip[0] == '|')
			{
				close (fd[0]);
				dup2(fd[1], 1);
				close(fd[1]);
			}
			execve(tok->path, tok->str, env);
			perror("execve");
			exit(EXIT_FAILURE);
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
	while(wait(NULL) != -1);
}

void	 execute_external_cmd(t_tok *tok, char **env, int fd)
{
	char	**args;
	pid_t	pid;
	int		status;
	int fd1;

	tok = check_cmd(tok, env);
	if (tok->pip && tok->pip[0] == '|')
	{
		execute_with_pipe(tok, env);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			// print_tok(tok);
			if (execve(tok->path, tok->str, env) == -1)
			{
				perror("minishell failed");
				exit(EXIT_FAILURE);
			}
		}
		if (pid > 0)
		{
			waitpid(pid, &status, 0);
		}
		else
		{
			perror("fork failed");
			return ;
		}
	}
}
