/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:19:10 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/30 00:07:14 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "execution.h"

extern	int g_flag;

/*a ajouter ft_clear exit*/

void	ft_execve(t_tok *tok, char **env)
{
	if (tok->path)
	{
		if (execve(tok->path, tok->str, env) == -1)
		{
			perror("minishell");
			if (errno == EACCES)
				exit(EXIT_NO_PERMISSION);
			else if (errno == ENOENT)
				exit(EXIT_NOT_FOUND);
			else
				exit(EXIT_FAILURE);
		}
	}
}

void	execute_cases(t_tok *tok, t_shell *shell, char **env)
{
	int	exit_status;

	tok = check_cmd(tok, shell, env);
	if (!tok)
	{
		exit_status = shell->exit_status;
		ft_clear(env, shell, tok);
		free_tok(tok);
		exit(exit_status);
	}
	if (!execute_redirect(tok, env, shell))
	{
		ft_clear(env, shell, tok);
		free_tok(tok);
		exit(EXIT_FAILURE);
	}
	if (tok->str && is_built_in(tok->str[0], env))
	{
		exit_status = execute_built_in(tok, shell, env);
		free_tok(tok);
		ft_clear(env, shell, tok);
		exit(exit_status);
	}
	else
		ft_execve(tok, env);
}

void	tok_error_handling(t_tok *tok, t_shell *shell, char **env)
{
	int		exit_status;

	exit_status = shell->exit_status;
	close(shell->saved_stdin);
	close(shell->saved_stdout);
	ft_clear(env, shell, tok);
	exit(exit_status);
}


void	execute_with_execve(t_tok *tok, t_shell *shell ,char **env)
{
	pid_t	pid;
	int		status;
	int		sig;


	g_flag = 1;
	pid = fork();
	if (pid < 0)
		perror("fork");
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		tok = check_cmd(tok, shell, env);
		if (!tok)
			tok_error_handling(tok, shell, env);
		ft_execve(tok, env);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == SIGQUIT)
			{
				ft_printf(2, "Quit (core dumped)\n");
				shell->exit_status = 131;
			}
			else if (sig == SIGINT)
				printf("\n");
		}
		else if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
	}
	g_flag = 0;
}
