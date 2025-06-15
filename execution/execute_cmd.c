/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:57:59 by hes-saou          #+#    #+#             */
/*   Updated: 2025/06/15 18:53:42 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	execute_cmd(t_tok *tok, char **env, int fd, t_shell *shell)
{
	// print_tok(tok);
	if (tok->execute)
		execute_executable(tok, env);
	if (tok->pip && tok->pip[0] == '|')
		execute_with_pipe(tok, env, shell);
	else
	{
		if(is_built_in(tok->str[0], env))
			execute_built_in(tok, shell, env);
		else
			execute_external_cmd(tok, env, shell, 0);
	}
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
				{
					execute_built_in(tok, shell, env);
					exit(shell->exit_status);
				}
			}
			else
				execute_external_cmd(tok, env, shell, 1);
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

void	 execute_external_cmd(t_tok *tok, char **env, t_shell *shell, int flag)
{
	pid_t	pid;
	int		status;

	tok = check_cmd(tok, env);
	if (flag == 1)
	{
		if (execve(tok->path, tok->str, env) == -1)
			{
				perror("minishell failed");
				exit(EXIT_FAILURE);
			}
	}
	// if (tok->pip && tok->pip[0] == '|')
	// 	execute_with_pipe(tok, env, shell);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (execve(tok->path, tok->str, env) == -1)
			{
				perror("minishell failed");
				exit(EXIT_FAILURE);
			}
		}
		if (pid > 0)
			waitpid(pid, &status, 0);
		else
		{
			perror("fork failed");
			return ;
		}
	}
}
