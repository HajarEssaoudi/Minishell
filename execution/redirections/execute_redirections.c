/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:45:05 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/26 01:12:25 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	execute_redirect(t_tok *tok, char **env, t_shell *shell)
{
	t_rederict	*tmp;
	char		*last_out;
	char		*last_in;
	char		*last_append;
	int			fd;

	last_out = NULL;
	last_in = NULL;
	last_append = NULL;
	tmp = tok->redirect;
	while (tmp)
	{
		if (!ft_strcmp(tmp->flag, "1") || !tmp->filename || !tmp->filename[0])
		{
				ft_printf(2, "minishell : ambiguous redirect\n");
				return ;
		}
		if (ft_strcmp(tmp->type, ">") == 0)
		{
			fd = open(tmp->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror("open");
				shell->exit_status = EXIT_FAILURE;
				return ;
			}
			last_out = tmp->filename;
		}
		else if (ft_strcmp(tmp->type, "<") == 0)
		{
			fd = open(tmp->filename, O_RDONLY);
			if (fd < 0)
			{
				perror("open");
				shell->exit_status = EXIT_FAILURE;
				return ;
			}
			last_in = tmp->filename;
		}
		else if (ft_strcmp(tmp->type, ">>") == 0)
		{
			fd = open(tmp->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
			{
				perror("open");
				shell->exit_status = EXIT_FAILURE;
				return ;
			}
			last_append = tmp->filename;
		}
		tmp = tmp->next;
	}
	if (last_in)
		ft_in(tok, last_in, env, shell);
	if (last_out)
		ft_out(tok, last_out, env, shell);
	if (last_append)
		ft_append(tok, last_append, env, shell);
}
