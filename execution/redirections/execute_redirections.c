/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:45:05 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/06 00:16:50 by hes-saou         ###   ########.fr       */
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
		shell->exit_status = EXIT_FAILURE;
		return (0);
	}
	redir->last_append = filename;
	close(fd);
	return (1);
}

void	last_redir(t_redir *redir, t_shell *shell)
{
	if (redir->last_in)
		ft_in(redir->last_in, shell);
	if (redir->last_append)
		ft_append(redir->last_append, shell);
	if (redir->last_out)
		ft_out(redir->last_out, shell);
}

void	init_redirect(t_redir *redir)
{
	redir->last_out = NULL;
	redir->last_in = NULL;
	redir->last_append = NULL;
}

int	execute_redirect(t_tok *tok, t_shell *shell)
{
	t_rederict	*tmp;
	t_redir		redir;

	init_redirect(&redir);
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
	last_redir(&redir, shell);
	return (1);
}
