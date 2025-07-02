/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:45:05 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/02 13:49:02 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

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
	if (delimiter)
		ft_herdoc(tok, delimiter, env, shell);
	if (last_in)
		ft_in(tok, last_in, env, shell);
	if (last_out)
		ft_out(tok, last_out ,env, shell);
	if (last_append)
		ft_append(tok, last_append, env, shell);
}
