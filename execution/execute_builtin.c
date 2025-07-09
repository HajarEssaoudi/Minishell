/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:28:02 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/08 23:06:11 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	execute_built_in(t_tok *tok, t_shell *shell, char **env)
{
	if (tok->str[0] == NULL)
		return ;
	if (ft_strcmp("cd", tok->str[0]) == 0)
		execute_cd(tok, shell);
	else if (ft_strcmp("pwd", tok->str[0]) == 0)
		execute_pwd(shell);
	else if (ft_strcmp("echo", tok->str[0]) == 0)
		execute_echo(tok);
	else if (ft_strcmp("env", tok->str[0]) == 0)
		execute_env(env);
	else if (ft_strcmp("exit", tok->str[0]) == 0)
		execute_exit(tok);
	else if (ft_strcmp("unset", tok->str[0]) == 0)
		execute_unset(tok, shell);
	else if (ft_strcmp("export", tok->str[0]) == 0)
		execute_export(tok, shell);
}
