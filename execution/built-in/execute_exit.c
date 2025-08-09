/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:16:30 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/09 02:14:52 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static void	exit_with_error(t_tok *tok, t_shell *shell, char **env)
{
	shell->exit_status = 2;
	ft_putstr_fd("exit\n", 2);
	ft_printf(2, "Minishell: exit: %s: numeric argument required\n",
		tok->str[1]);
	tok_error_handling(tok, shell, env);
}

static void	exit_with_value(t_tok *tok, t_shell *shell, char **env)
{
	shell->exit_status = (unsigned char)ft_atoi(tok->str[1]);
	write(2, "exit\n", 6);
	tok_error_handling(tok, shell, env);
}

static void	handle_exit_args(t_tok *tok, t_shell *shell, char **env)
{
	if (ft_atoi(tok->str[1]) >= __LONG_LONG_MAX__)
		exit_with_error(tok, shell, env);
	if (!ft_str_num(tok->str[1]))
		exit_with_error(tok, shell, env);
	if (tok->str[2])
	{
		ft_putstr_fd("exit\n", 2);
		shell->exit_status = 1;
		write(2, "Minishell: exit: too many arguments\n", 37);
	}
	else
		exit_with_value(tok, shell, env);
}

int	execute_exit(t_tok *tok, t_shell *shell, char **env)
{
	if (tok->str[1])
	{
		handle_exit_args(tok, shell, env);
		return (shell->exit_status);
	}
	else
	{
		ft_printf(2, "exit\n");
		tok_error_handling(tok, shell, env);
	}
	return (shell->exit_status);
}
