/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:45:05 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/15 09:37:04 by mabdelha         ###   ########.fr       */
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
		// printf("filename => %s\n", tmp->type);
		// if (tmp->flag)
			// printf("tmp->flag %s\n", tmp->flag);
		if (!ft_strcmp(tmp->flag, "1") || !tmp->filename)
		{
				ft_printf(2, "minishell : ambiguous redirect\n");
				return ;
		}
		// printf("%s\n", tmp->flag);
		if (ft_strcmp(tmp->type, ">") == 0)
			ft_out(tok, tmp->filename, env, shell);
		else if (ft_strcmp(tmp->type, "<") == 0)
			ft_in(tok, tmp->filename, env, shell);
		else if (ft_strcmp(tmp->type, ">>") == 0)
			ft_append(tok, tmp->filename, env, shell);
		// printf("int => %d\n", tmp->flag);
		// pid = fork();
		// if (pid == 0)
		// {
			
			// if (last_in)
			// 	ft_in(tok, last_in, env, shell);
			// if (last_out)
			// 	ft_out(tok, last_out, env, shell);
			// if (last_append)
			// 	ft_append(tok, last_append, env, shell);
		// }
		// else if (pid > 0)
		// 	waitpid(pid, &status, 0);
		tmp = tmp->next;
	}
}
