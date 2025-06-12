/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:05:30 by hes-saou          #+#    #+#             */
/*   Updated: 2025/06/12 15:18:07 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cd(t_tok *tok, t_shell *shell)
{
	char	*home_path;

	shell->old_path = get_path();
	if (shell->old_path == NULL)
	{
		// change pwd and oldpwd
	}
	if (chdir(tok->str[1]) == -1)
		perror("cd");
	shell->current_path = get_path();
	if (shell->current_path == NULL)
		ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n",
			2);
	change_env_paths(shell);
}

void	execute_pwd(t_tok *tok, t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			printf("%s\n", tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
}

void	execute_env(t_tok *tok, t_shell *shell, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}
