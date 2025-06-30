/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:57:59 by hes-saou          #+#    #+#             */
/*   Updated: 2025/06/30 17:22:18 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	execute_cmd(t_tok *tok, char **env, t_shell *shell)
{
	if (tok->execute)
		execute_executable(tok, env);
	else if (tok->redirect)
		execute_redirect(tok, env, shell);
	else if (tok->pip && tok->pip[0] == '|')
		execute_with_pipe(tok, env, shell);
	else if(is_built_in(tok->str[0], env))
		execute_built_in(tok, shell, env);
	else
		execute_external_cmd(tok, env, 1);
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

void	 execute_external_cmd (t_tok *tok, char **env, int flag)
{
	pid_t	pid;
	int		status;

	tok = check_cmd(tok, env);
	if (!tok)
		return ;
	if (flag == 0)
	{
		if (execve(tok->path, tok->str, env) == -1)
		{
			perror("minishell failed");
			exit(EXIT_FAILURE);
		}
	}
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
