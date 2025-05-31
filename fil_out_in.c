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

void	ft_out(t_tok *tok, char **cp_env, t_shell *shell)
{
	t_tok	*tmp;
	int		fd;
	int		fd1;
	int		i;
	int		j;

	i = 0;
	while (tok->output[i])
		i++;
	j = 1;
	while (j < i - 1)
	{
		close(open(tok->output[j], O_CREAT | O_WRONLY | O_TRUNC, 0644));
		j += 2;
	}
	fd = open(tok->output[i - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	
	if (tok->path && tok->str)
	{
		tok->env = cp_env;
		tmp = tok;
		execute_cmd(tmp, tok->env, fd, shell);
	}
	
}
