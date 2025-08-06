/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:31:36 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/05 21:50:23 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*check_ext(char *input, char **cp_env)
{
	char	*path;
	char	**path_split;
	char	*found;
	char	*cmd;

	found = NULL;
	path = get_env_var(cp_env, "PATH");
	if (path)
		path_split = ft_split(path, ':');
	else
		return (NULL);
	cmd = check_cmd_acces(input, path_split, &found);
	if (cmd)
		return (cmd);
	free_str(path_split);
	if (found)
	{
		free(found);
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

int	check_is_dir(t_tok *tok, t_shell *shell)
{
	struct stat	dir;

	dir.st_mode = 0;
	stat(tok->path, &dir);
	if (S_ISDIR(dir.st_mode))
	{
		ft_putstr_fd("Minishell: Is a directory\n", 2);
		free_tok(tok);
		shell->exit_status = EXIT_NO_PERMISSION;
		return (1);
	}
	return (0);
}

int	absolut_path(t_tok *tok, t_shell *shell)
{
	if (check_is_dir(tok, shell))
		return (1);
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
