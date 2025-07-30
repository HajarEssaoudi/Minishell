/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 03:22:14 by mabdelha          #+#    #+#             */
/*   Updated: 2025/07/30 22:01:54 by hes-saou         ###   ########.fr       */
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
		rl_redisplay();
	}
}

void	ft_handl_herdoc(int sig)
{
	(void)sig;
	g_flag = 1;
	printf("\n");
	exit(130);
}
