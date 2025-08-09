/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_execve_helpers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 23:51:15 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/09 02:11:05 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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

void	ft_clean(t_tok *tok, t_shell *shell, char **env)
{
	ft_clear(env, shell);
	free_tok(tok);
}

void	execute_cases(t_tok *tok, t_shell *shell, char **env)
{
	int	exit_status;

	if (tok->str && !is_built_in(tok->str[0]))
		tok = check_cmd(tok, shell, env);
	if (!tok)
	{
		exit_status = shell->exit_status;
		ft_clean(tok, shell, env);
		exit(exit_status);
	}
	if (!execute_redirect(tok, shell))
	{
		ft_clean(tok, shell, env);
		exit(EXIT_FAILURE);
	}
	if (tok->str && is_built_in(tok->str[0]))
	{
		exit_status = execute_built_in(tok, shell, env);
		ft_clean(tok, shell, env);
		exit(exit_status);
	}
	else
		ft_execve(tok, env);
	exit(shell->exit_status);
}

void	tok_error_handling(t_tok *tok, t_shell *shell, char **env)
{
	int	exit_status;

	exit_status = shell->exit_status;
	if (shell->saved_stdin != -1)
		close(shell->saved_stdin);
	if (shell->saved_stdout != -1)
		close(shell->saved_stdout);
	if (tok && tok->heredoc_fd != -1)
		close(tok->heredoc_fd);
	ft_clear(env, shell);
	if (tok)
		free_tok(tok);
	exit(exit_status);
}
