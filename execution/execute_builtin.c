/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:28:02 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/19 11:11:43 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	execute_built_in(t_tok *tok, t_shell *shell, char **env)
{
	if (tok->str[0] == NULL)
		return ;
	tok = check_cmd(tok, env);
	if (!tok)
	{
		shell->exit_status = EXIT_NOT_FOUND;
		exit(shell->exit_status);
	}
	if (ft_strcmp("cd", tok->str[0]) == 0)
		shell->exit_status = execute_cd(tok, shell);
	else if (ft_strcmp("pwd", tok->str[0]) == 0)
		shell->exit_status = execute_pwd(shell);
	else if (ft_strcmp("echo", tok->str[0]) == 0)
		execute_echo(tok);
	else if (ft_strcmp("env", tok->str[0]) == 0)
		shell->exit_status = execute_env(tok, env);
	else if (ft_strcmp("exit", tok->str[0]) == 0)
		execute_exit(tok, shell);
	else if (ft_strcmp("unset", tok->str[0]) == 0)
		shell->exit_status = execute_unset(tok, shell);
	else if (ft_strcmp("export", tok->str[0]) == 0)
		shell->exit_status = execute_export(tok, shell);
}
