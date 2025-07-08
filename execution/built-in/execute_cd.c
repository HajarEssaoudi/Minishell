/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:07:40 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/08 01:43:06 by hes-saou         ###   ########.fr       */
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

static void	change_old_path(t_shell *shell)
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
}

static void	change_new_path(t_shell *shell)
{
	t_env	*tmp;

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

/* change pwd and oldpwd in the if*/

void	execute_cd(t_tok *tok, t_shell *shell)
{
	char	*home_path;

	shell->old_path = get_path();
	if (shell->old_path == NULL)
	{
	}
	if (chdir(tok->str[1]) == -1)
		perror("cd");
	shell->current_path = get_path();
	if (shell->current_path == NULL)
		ft_putstr_fd("cd: error retrieving current directory:"
			" getcwd: cannot access parent directories:"
			"No such file or directory\n", 2);
	change_old_path(shell);
	change_new_path(shell);
}
