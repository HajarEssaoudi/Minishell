/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:16:30 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/09 00:12:54 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static void	exit_with_error(t_tok *tok, t_shell *shell, char **env)
{
	shell->exit_status = 2;
	ft_putstr_fd("exit\n", 1);
	ft_printf(2, "Minishell: exit: %s: numeric argument required\n",
		tok->str[1]);
	free_tok(tok);
	tok_error_handling(shell, env);
}

static void	exit_with_value(t_tok *tok, t_shell *shell, char **env)
{
	shell->exit_status = (unsigned char)ft_atoi(tok->str[1]);
	ft_putstr_fd("exit\n", 1);
	free_tok(tok);
	tok_error_handling(shell, env);
}

static void	handle_exit_args(t_tok *tok, t_shell *shell, char **env)
{
	if (ft_atoi(tok->str[1]) >= __LONG_LONG_MAX__)
		exit_with_error(tok, shell, env);
	if (!ft_str_num(tok->str[1]))
		exit_with_error(tok, shell, env);
	if (tok->str[2])
	{
		ft_putstr_fd("exit\n", 1);
		shell->exit_status = 1;
		ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
	}
	else
		exit_with_value(tok, shell, env);
}

int	execute_exit(t_tok *tok, t_shell *shell, char **env)
{
	shell->exit_status = 0;
	if (tok->str[1])
	{
		handle_exit_args(tok, shell, env);
		return (shell->exit_status);
	}
	else
	{
		printf("exit\n");
		free_tok(tok);
		tok_error_handling(shell, env);
	}
	return (0);
}
