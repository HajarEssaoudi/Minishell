/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 03:22:14 by mabdelha          #+#    #+#             */
/*   Updated: 2025/08/02 14:59:30 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

extern int	g_flag;

void	ft_handl(int sig)
{
	if (!g_flag && sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_handl_herdoc(int sig)
{
	t_clean	*cleaner;

	(void)sig;
	g_flag = 1;
	printf("\n");
	cleaner = cleane_heredoc();
	close(cleaner->fd);
	free_tok(cleaner->tok);
	ft_clear(cleaner->env, cleaner->shell, cleaner->tok);
	exit(130);
}
