/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fil_out_in.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdelhaqmarouan <abdelhaqmarouan@student.42.fr>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-09 10:35:35 by abdelhaqmarouan   #+#    #+#             */
/*   Updated: 2025-05-09 10:35:35 by abdelhaqmarouan  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void    ft_out(t_tok *tok, char **cp_env)
{
	t_tok	*tmp;
    if (tok->output && tok->filename)
    {
        int fd = open(tok->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
        int fd1 = dup(1);
        dup2(fd, 1);
        close(fd);
        tok->env = cp_env;
		tmp = tok;
		execute_cmd(tmp, tok->env);
        dup2(fd1, 1);
        close(fd1);
    }
}