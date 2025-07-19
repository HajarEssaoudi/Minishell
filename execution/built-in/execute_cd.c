/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:07:40 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/19 10:25:33 by hes-saou         ###   ########.fr       */
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

static void	search_and_change(t_shell *shell, char *key, char *path)
{
	t_env	*tmp;

	if (!path)
		return ;
	tmp = shell->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(path);
			break ;
		}
		tmp = tmp->next;
	}
}

static char	*search_in_env(t_shell *shell, char *key)
{
	t_env	*tmp;

	tmp = shell->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	execute_cd(t_tok *tok, t_shell *shell)
{
	shell->old_path = get_path();
	if (shell->old_path == NULL)
	{
		shell->old_path = ft_strdup(search_in_env(shell, "PWD"));
	}
	if (chdir(tok->str[1]) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	shell->current_path = get_path();
	if (shell->current_path == NULL)
	{
		ft_printf(2, "cd: error retrieving current directory:"
			" getcwd: cannot access parent directories:"
			"No such file or directory\n");
		return (0);
	}
	search_and_change(shell, "PWD", shell->current_path);
	search_and_change(shell, "OLDPWD", shell->old_path);
	free(shell->old_path);
	free(shell->current_path);
	return (0);
}
