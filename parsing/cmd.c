/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:31:36 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/30 19:08:19 by hes-saou         ###   ########.fr       */
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

	i = 0;
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
			free_str(path_split);
			return (cmd);
		}
		free(cmd);
		i++;
	}
	free_str(path_split);
	return (NULL);
}

char	*relative_path(t_tok *tok, char **cp_env)
{
	char	*ex;

	ex = check_ext(tok->path, cp_env);
	if (ex)
	{
		free(tok->path);
		tok->path = ft_strdup(ex);
		free(ex);
	}
	else if (!ex)
	{
		free(tok->path);
		write(2, "Minishell:command not found\n",
			ft_strlen("Minishell:command not found\n"));
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
	return (0);
}

t_tok	*check_cmd(t_tok *tok, t_shell *shell, char **cp_env)
{
	if (tok->path)
	{
		if (!ft_strchr(tok->path, '/'))
		{
			tok->path = relative_path(tok, cp_env);
			if (!tok->path)
			{
				free_tok(tok);
				shell->exit_status = EXIT_NOT_FOUND;
				return (NULL);
			}
		}
		else if (absolut_path(tok, shell))
			return (NULL);
	}
	return (tok);
}
