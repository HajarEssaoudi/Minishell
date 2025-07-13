/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:45:05 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/13 09:44:27 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	execute_redirect(t_tok *tok, char **env, t_shell *shell)
{
	t_rederict	*tmp;
	char		*last_out;
	char		*last_in;
	char		*last_append;
	pid_t		pid;
	int			status;
	int			flag;

	last_out = NULL;
	last_in = NULL;
	last_append = NULL;
	tmp = tok->redirect;
	flag = 0;
	while (tmp)
	{
		if (!ft_strcmp(tmp->flag, "1"))
			flag = 1;
		// printf("%s\n", tmp->flag);
		if (ft_strcmp(tmp->type, ">") == 0)
			last_out = tmp->filename;
		else if (ft_strcmp(tmp->type, "<") == 0)
			last_in = tmp->filename;
		else if (ft_strcmp(tmp->type, ">>") == 0)
			last_append = tmp->filename;
		// printf("int => %d\n", tmp->flag);
		tmp = tmp->next;
	}
	pid = fork();
	if (pid == 0)
	{
		if (flag == 1)
		{
			printf ("minishell : ambiguous redirect\n");
			return ;
		}
		if (last_in)
			ft_in(tok, last_in, env, shell);
		if (last_out)
			ft_out(tok, last_out, env, shell);
		if (last_append)
			ft_append(tok, last_append, env, shell);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
}
