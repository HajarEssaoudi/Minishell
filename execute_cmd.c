/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:55:03 by hes-saou          #+#    #+#             */
/*   Updated: 2025/05/22 17:12:28 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int global = 0;
void	execute_built_in(t_tok *tok)
{
	if (ft_strncmp("cd", tok->str[0], ft_strlen(tok->str[0])) == 0)
		execute_cd(tok);
	else if (ft_strncmp("pwd", tok->str[0], ft_strlen(tok->str[0])) == 0)
		execute_pwd(tok);
	else if (ft_strncmp("echo", tok->str[0], ft_strlen(tok->str[0])) == 0)
		execute_echo(tok);
	else if (ft_strncmp("env", tok->str[0], ft_strlen(tok->str[0])) == 0)
		execute_env(tok);
	else if (ft_strncmp("exit", tok->str[0], ft_strlen(tok->str[0])) == 0)
		execute_exit(tok);
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
		global = 3;
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
		signal(SIGINT, SIG_IGN);
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

void	execute_cmd(t_tok *tok, char **env, int fd)
{
	if (tok->execute)
		execute_executable(tok, env);
	else if(is_built_in(tok->str[0], env))
		execute_built_in(tok);
	else
		execute_simple_cmd(tok, env, fd);
}