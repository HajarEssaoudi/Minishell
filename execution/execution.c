/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:40:23 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/02 15:42:41 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	execute_cmd(t_tok *tok, t_shell *shell, char **env)
{
	t_tok	*tmp;
	int		fd[2];
	int		prev_fd;
	pid_t	pid1;
	int		status;

	tok = check_cmd(tok, env);
	if (!tok)
		return ;
	prev_fd = -1;
	tmp = tok;
	while (tmp)
	{
		if (tmp->pip && tmp->pip[0] == '|')
		{
			if (pipe(fd) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if(is_built_in(tmp->str[0], env))
			{
				execute_built_in(tmp, shell, env);
				return ;
			}
		}
		pid1 = fork();
		if (pid1 == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid1 == 0)
		{
			/*if not the first cmd*/
			if (prev_fd != -1)
			{
				dup2(prev_fd, 0);
				close(prev_fd);
			}
			/*not last cmd*/
			if (tmp->pip && tmp->pip[0] == '|')
			{
				close (fd[0]);
				dup2(fd[1], 1);
				close(fd[1]);
			}
			// execute_redirect(tmp, env, shell);
			if(is_built_in(tmp->str[0], env))
			{
				execute_built_in(tmp, shell, env);
				exit(0);
			}
			if (!is_built_in(tmp->str[0], env))
				ft_execve(tmp, env);
		}
		else
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (tmp->pip && tmp->pip[0] == '|')
			{
				close(fd[1]);
				prev_fd = fd[0];
			}
			else
			{
				if (prev_fd != -1)
					close(prev_fd);
				break;
			}
		}
		tmp = tmp->next;
	}
	while (wait(&status) > 0);
}
