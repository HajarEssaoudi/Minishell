/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:45:05 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/03 07:49:42 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	app_red(t_redir *redir, char *filename, t_shell *shell)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open");
		if (errno == EACCES)
			shell->exit_status = EXIT_NO_PERMISSION;
		else if (errno == ENOENT)
			shell->exit_status = EXIT_NOT_FOUND;
		else
			shell->exit_status = EXIT_FAILURE;
		return (0);
	}
	redir->last_append = filename;
	close(fd);
	return (1);
}

void	last_redir(t_tok *tok, char **env, t_redir *redir, t_shell *shell)
{
	if (redir->last_in)
		ft_in(tok, redir->last_in, env, shell);
	if (redir->last_append)
		ft_append(tok, redir->last_append, env, shell);
	if (redir->last_out)
		ft_out(tok, redir->last_out, env, shell);
}

int	execute_redirect(t_tok *tok, char **env, t_shell *shell)
{
	t_rederict	*tmp;
	t_redir		redir;

	redir.last_out = NULL;
	redir.last_in = NULL;
	redir.last_append = NULL;
	tmp = tok->redirect;
	while (tmp)
	{
		if (!check_ambg(tmp, shell))
			return (0);
		if (ft_strcmp(tmp->type, ">") == 0 && !out_red(&redir, tmp->filename,
				shell))
			return (0);
		else if (ft_strcmp(tmp->type, "<") == 0 && !in_red(&redir,
				tmp->filename, shell))
			return (0);
		else if (ft_strcmp(tmp->type, ">>") == 0 && !app_red(&redir,
				tmp->filename, shell))
			return (0);
		else if (ft_strcmp(tmp->type, "<<") == 0)
			redir.last_in = NULL;
			
		tmp = tmp->next;
	}
	last_redir(tok, env, &redir, shell);
	return (1);
}
