/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:31:36 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/02 11:06:55 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/execution.h"
#include "parsing.h"

char	*get_dir(char *input, char *path)
{
	char	*cmd;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	cmd = ft_strjoin(tmp, input);
	free(tmp);
	return (cmd);
}

char	*check_ext(char *input, char **cp_env)
{
	int		i;
	char	*path;
	char	**path_split;
	char	*cmd;
	char	*found_without_perm;

	i = 0;
	found_without_perm = NULL;
	path = get_env_var(cp_env, "PATH");
	if (path)
		path_split = ft_split(path, ':');
	else
		return (NULL);
	while (path_split[i])
	{
		cmd = get_dir(input, path_split[i]);
		if (access(cmd, F_OK) == 0)
		{
			if (access(cmd, X_OK) == 0)
			{
				free_str(path_split);
				if (found_without_perm)
					free(found_without_perm);
				return (cmd);
			}
			else if (!found_without_perm)
				found_without_perm = ft_strdup(cmd);
		}
		free(cmd);
		i++;
	}
	free_str(path_split);
	if (found_without_perm)
	{
		free(found_without_perm);
		return (input);
	}
	return (NULL);
}

char	*relative_path(t_tok *tok, char **cp_env, t_shell *shell)
{
	char	*ex;

	ex = check_ext(tok->path, cp_env);
	if (ex && ft_strcmp(ex, tok->path) != 0)
	{
		free(tok->path);
		tok->path = ft_strdup(ex);
		free(ex);
	}
	else if (ex && ft_strcmp(ex, tok->path) == 0)
	{
		ft_printf(2, "Minishell: %s: Permission denied\n", ex);
		free(tok->path);
		shell->exit_status = EXIT_NO_PERMISSION;
		return (NULL);
	}
	else if (!ex)
	{
		free(tok->path);
		write(2, "Minishell:command not found\n",
			ft_strlen("Minishell:command not found\n"));
		shell->exit_status = EXIT_NOT_FOUND;
		return (NULL);
	}
	return (tok->path);
}

int	absolut_path(t_tok *tok, t_shell *shell)
{
	struct stat	dir;

	dir.st_mode = 0;
	stat(tok->path, &dir);
	if (S_ISDIR(dir.st_mode))
	{
		ft_putstr_fd("Minishell: Is a directory\n", 2);
		shell->exit_status = EXIT_NO_PERMISSION;
		return (1);
	}
	else if (access(tok->path, F_OK) != 0)
	{
		ft_printf(2, "Minishell: %s: No such file or directory\n", tok->path);
		shell->exit_status = EXIT_NOT_FOUND;
		free_tok(tok);
		return (1);
	}
	else if (access(tok->path, X_OK) != 0)
	{
		ft_printf(2, "Minishell: %s: Permission denied\n", tok->path);
		shell->exit_status = EXIT_NO_PERMISSION;
		free_tok(tok);
		return (1);
	}
	return (0);
}

t_tok	*check_cmd(t_tok *tok, t_shell *shell, char **cp_env)
{
	if (tok->path)
	{
		if (!tok->path || !tok->path[0])
		{
			write(2, "Minishell:command not found\n",
			ft_strlen("Minishell:command not found\n"));
			free_tok(tok);
			shell->exit_status = EXIT_NOT_FOUND;
			return (NULL);
		}
		if (!ft_strchr(tok->path, '/'))
		{
			tok->path = relative_path(tok, cp_env, shell);
			if (!tok->path)
			{
				free_tok(tok);
				return (NULL);
			}
		}
		else if (absolut_path(tok, shell))
			return (NULL);
	}
	return (tok);
}
