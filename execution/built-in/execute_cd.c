/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:07:40 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/09 02:54:40 by mabdelha         ###   ########.fr       */
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

static int	update_path(t_shell *shell)
{
	if (shell->current_path)
	{
		free(shell->current_path);
		shell->current_path = get_path();
	}
	if (shell->current_path == NULL)
	{
		ft_putstr_fd("cd: error retrieving current directory:"
			" getcwd: cannot access parent directories:"
			"No such file or directory\n",
			2);
		return (0);
	}
	search_and_change(shell, "PWD", shell->current_path);
	search_and_change(shell, "OLDPWD", shell->old_path);
	return (1);
}

int	execute_cd(t_tok *tok, t_shell *shell)
{
	if (shell->old_path)
	{
		free(shell->old_path);
		shell->old_path = NULL;
	}
	shell->old_path = ft_strdup(search_in_env(shell, "PWD"));
	if (!tok->str[1])
	{
		write(2,
			"Minishell: syntax error: expected relative or absolute path\n",
			61);
		return (2);
	}
	if (tok->str[2])
	{
		write(2, "Minishell: cd: too many arguments\n", 35);
		return (1);
	}
	if (chdir(tok->str[1]) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	update_path(shell);
	return (0);
}
