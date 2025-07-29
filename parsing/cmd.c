/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:31:36 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/29 03:20:39 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static char	*is_built_in(char *input)
{
	char	*cmd[] = {"cd", "echo", "pwd", "export", "unset", "env", "exit",
			NULL};
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (ft_strncmp(input, cmd[i], ft_strlen(input)) == 0)
		{
			return (cmd[i]);
		}
		i++;
	}
	return (NULL);
}

char	*relative_path(t_tok *tok, char **cp_env)
{
	char	*in;
	char	*ex;

	in = is_built_in(tok->path);
	if (!in)
		ex = check_ext(tok->path, cp_env);
	if (in)
	{
		free(tok->path);
		tok->path = ft_strdup(in);
	}
	else if (ex)
	{
		free(tok->path);
		tok->path = ft_strdup(ex);
		free(ex);
	}
	else if (!ex && !in)
	{
		free(tok->path);
		write(2, "Minishell:command not found\n",
			ft_strlen("Minishell:command not found\n"));
		return (NULL);
	}
	return (tok->path);
}

t_tok	*check_cmd(t_tok *tok, char **cp_env)
{
	// while (tok)
	// {
		if (tok->path)
		{
			struct stat dr;
			mode_t mode;
			stat(tok->path, &dr);
			mode = dr.st_mode;
			if (S_ISDIR(mode))
			{
				ft_printf(2, "Minishell: Is a directory: %s\n",
						tok->path);
				free_tok(tok);
				return (NULL);
			}
			if (!ft_strchr(tok->path, '/'))
			{
				tok->path = relative_path(tok, cp_env);
				if (!tok->path)
				{
					free_tok(tok);
					return (NULL);
				}
			}
			else
			{
				if (access(tok->path, F_OK) != 0)
				{
					ft_printf(2, "Minishell: command not found: %s\n",
						tok->path);
					return (NULL);
				}
			}
		}
		// tok = tok->next;
	// }
	return (tok);
}
