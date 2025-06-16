/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:07:40 by hes-saou          #+#    #+#             */
/*   Updated: 2025/06/15 22:57:06 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char	*get_path(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		return (NULL);
	}
	return (cwd);
}

void	change_env_paths(t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "OLDPWD") == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(shell->old_path);
			break ;
		}
		tmp = tmp->next;
	}
	tmp = shell->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			free(tmp->value);
			if (shell->current_path)
				tmp->value = ft_strdup(shell->current_path);
			else
				return ;
			break ;
		}
		tmp = tmp->next;
	}
}

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