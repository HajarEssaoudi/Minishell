/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:40:23 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/08 18:09:44 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	execute_without_pipe(t_tok *tok, t_shell *shell, char **env)
{
	int	saved_stdout;
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
		execute_redirect(tok, env, shell);
	if (tok->str && tok->str[0])
	{
		if (is_built_in(tok->str[0], env))
			execute_built_in(tok, shell, env);
	}
	else
		execute_with_execve(tok, env);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

void	execute_cmd(t_tok *tok, t_shell *shell, char **env)
{
	t_tok		*tmp;
	t_rederict	*redir;

	tmp = tok;
	while (tmp)
	{
		tmp->heredoc_fd = -1;
		redir = tmp->redirect;
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
		execute_with_pipe(tok, env, shell);
	else
		execute_without_pipe(tok, shell, env);
}
