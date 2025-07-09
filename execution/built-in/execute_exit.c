/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:16:30 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/09 11:41:54 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static void	exit_with_error(t_tok *tok, t_shell *shell)
{
	shell->exit_status = 2;
	printf("exit\n");
	// ft_clear(shell);
	printf("Minishell: exit: %s: numeric argument required\n", tok->str[1]);
	exit(shell->exit_status);
}

static void	exit_with_value(t_tok *tok, t_shell *shell)
{
	shell->exit_status = (unsigned char)ft_atoi(tok->str[1]);
	printf("exit\n");
	// ft_clear(shell);
	exit(shell->exit_status);
}

static void	handle_exit_args(t_tok *tok, t_shell *shell)
{
	if (ft_atoi(tok->str[1]) >= __LONG_LONG_MAX__)
		exit_with_error(tok, shell);
	if (!ft_str_num(tok->str[1]))
		exit_with_error(tok, shell);
	if (tok->str[2])
	{
		printf("exit\n");
		shell->exit_status = 1;
		ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
	}
	else
		exit_with_value(tok, shell);
}

void	execute_exit(t_tok *tok, t_shell *shell)
{
	shell->exit_status = 0;
	if (tok->str[1])
		handle_exit_args(tok, shell);
	else
	{
		// ft_clear(shell);
		printf("exit\n");
		exit(shell->exit_status);
	}
}
