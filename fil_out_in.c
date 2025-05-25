/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fil_out_in.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdelhaqmarouan <abdelhaqmarouan@student.42.fr>  #+#  +:+      
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-09 10:35:35 by abdelhaqmarouan   #+#    #+#             */
/*   Updated: 2025-05-09 10:35:35 by abdelhaqmarouan  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_out(t_tok *tok, char **cp_env)
{
	t_tok	*tmp;
	int		fd;
	int		fd1;

	int i = 0;
	while (tok->output[i])
		i++;
	i--;
	while (i > 0)
	{
			fd = open(tok->output[i], O_CREAT | O_WRONLY | O_APPEND, 0644);
			fd1 = dup(1);
			dup2(fd, 1);
			close(fd);
			if (tok->path && tok->str)
			{
				tok->env = cp_env;
				tmp = tok;
				execute_cmd(tmp, tok->env);
			}
			dup2(fd1, 1);
			close(fd1);
		i -= 2;
	}
	
}
