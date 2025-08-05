/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 03:22:14 by mabdelha          #+#    #+#             */
/*   Updated: 2025/08/05 12:51:56 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

extern int	g_flag;

void	ft_handle(int sig)
{
	if (!g_flag && sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_handle_herdoc(int sig)
{
	t_clean	*cleaner;

	(void)sig;
	g_flag = 1;
	printf("\n");
	cleaner = clean_heredoc();
	close(cleaner->fd);
	free_tok(cleaner->tok);
	ft_clear(cleaner->env, cleaner->shell, cleaner->tok);
	free(cleaner->name);
	exit(130);
}
