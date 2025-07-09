/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:16:30 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/08 23:16:22 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static void	exit_with_error(t_tok *tok)
{
	tok->exit_status = 2;
	printf("exit\n");
	// ft_clear(shell);
	printf("Minishell: exit: %s: numeric argument required\n", tok->str[1]);
	exit(tok->exit_status);
}

static void	exit_with_value(t_tok *tok)
{
	tok->exit_status = (unsigned char)ft_atoi(tok->str[1]);
	printf("exit\n");
	// ft_clear(shell);
	exit(tok->exit_status);
}

static void	handle_exit_args(t_tok *tok)
{
	if (ft_atoi(tok->str[1]) >= __LONG_LONG_MAX__)
		exit_with_error(tok);
	if (!ft_str_num(tok->str[1]))
		exit_with_error(tok);
	if (tok->str[2])
	{
		printf("exit\n");
		tok->exit_status = 1;
		ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
	}
	else
		exit_with_value(tok);
}

void	execute_exit(t_tok *tok)
{
	tok->exit_status = 0;
	if (tok->str[1])
		handle_exit_args(tok);
	else
	{
		// ft_clear(shell);
		printf("exit\n");
		exit(tok->exit_status);
	}
}
