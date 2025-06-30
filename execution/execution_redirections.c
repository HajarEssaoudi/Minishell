/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:36:32 by hes-saou          #+#    #+#             */
/*   Updated: 2025/06/30 21:35:32 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	execute_redirect(t_tok *tok, char **env, t_shell *shell)
{
	t_rederict	*tmp;
	char		*delimiter = NULL;
	char		*last_out = NULL;
	char		*last_in = NULL;
	char		*last_append = NULL;
	pid_t		pid;
	int			status;

	tmp = tok->redirect;
	while (tmp)
	{
		if (ft_strcmp(tmp->type, ">") == 0)
			last_out = tmp->filename;
		else if (ft_strcmp(tmp->type, "<") == 0)
			last_in = tmp->filename;
		else if (ft_strcmp(tmp->type, ">>") == 0)
			last_append = tmp->filename;
		else if (ft_strcmp(tmp->type, "<<") == 0)
			delimiter = tmp->filename;
		tmp = tmp->next;
	}

	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		return;
	}
	if (pid == 0)
	{
		if (delimiter)
			ft_herdoc(tok, delimiter, env, shell);
		if (last_in)
			ft_in(tok, last_in, env, shell);
		if (last_out)
			ft_out(tok, last_out ,env, shell);
		if (last_append)
			ft_append(tok, last_append, env, shell);
		if (is_built_in(tok->str[0], env))
			execute_built_in(tok, shell, env);
		else
			execute_external_cmd(tok, env, 0);
		exit(0);
	}
	else
		waitpid(pid, &status, 0);
}
