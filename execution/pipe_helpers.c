/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 21:59:43 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/30 22:05:13 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	open_pipe(t_tok *tok, int *fd)
{
	if (tok->pip && tok->pip[0] == '|' && pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

void	check_herdoc_fd(t_tok *tok)
{
	if (tok->heredoc_fd != -1)
	{
		dup2(tok->heredoc_fd, STDIN_FILENO);
		close(tok->heredoc_fd);
	}
}

void	fork_error(void)
{
	perror("fork");
	if (errno == EACCES)
		exit(EXIT_NO_PERMISSION);
	else if (errno == ENOENT)
		exit(EXIT_NOT_FOUND);
	else
		exit(EXIT_FAILURE);
}
