/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_execve_helpers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 23:51:15 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/05 02:12:38 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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

void	ft_clean(t_tok *tok, t_shell *shell, char **env)
{
	ft_clear(env, shell, tok);
	free_tok(tok);
}

void	execute_cases(t_tok *tok, t_shell *shell, char **env)
{
	int	exit_status;

	if (tok->str && !is_built_in(tok->str[0], env))
		tok = check_cmd(tok, shell, env);
	if (!tok)
	{
		exit_status = shell->exit_status;
		ft_clean(tok, shell, env);
		exit(exit_status);
	}
	if (!execute_redirect(tok, env, shell))
	{
		ft_clean(tok, shell, env);
		exit(EXIT_FAILURE);
	}
	if (tok->str && is_built_in(tok->str[0], env))
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
	close(shell->saved_stdin);
	close(shell->saved_stdout);
	ft_clear(env, shell, tok);
	exit(exit_status);
}
