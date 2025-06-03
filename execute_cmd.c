/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:55:03 by hes-saou          #+#    #+#             */
/*   Updated: 2025/06/03 14:51:46 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int global = 0;

void	execute_built_in(t_tok *tok, t_shell *shell, char **env)
{
	if (ft_strcmp("cd", tok->str[0]) == 0)
		execute_cd(tok, shell);
	else if (ft_strcmp("pwd", tok->str[0]) == 0)
		execute_pwd(tok, shell);
	else if (ft_strcmp("echo", tok->str[0]) == 0)
		execute_echo(tok);
	else if (ft_strcmp("env", tok->str[0]) == 0)
		execute_env(tok, shell, env);
	else if (ft_strcmp("exit", tok->str[0]) == 0)
		execute_exit(tok, shell);
}

void	 execute_simple_cmd(t_tok *tok, char **env, int fd)
{
	char	**args;
	pid_t	pid;
	int		status;
	int fd1;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, ft_hand);
		if (tok->output)
		{
			fd1 = dup(1);
			dup2(fd, 1);
			close(fd);
		}
		if (execve(tok->path, tok->str, env) == -1)
		{
			perror("minishell failed");
			exit(EXIT_FAILURE);
		}
		if (tok->output)
		{
			dup2(fd1, 1);
			close(fd1);
		}
	}
	else if (pid > 0)
	{
		global = 0;
		signal(SIGINT, ft_hand);
		waitpid(pid, &status, 0);
	}
	else
	{
		perror("fork failed");
		return ;
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

void	execute_cmd(t_tok *tok, char **env, int fd, t_shell *shell)
{
	if (tok->execute)
		execute_executable(tok, env);
	else if(is_built_in(tok->str[0], env))
		execute_built_in(tok, shell, env);
	else
		execute_simple_cmd(tok, env, fd);
}