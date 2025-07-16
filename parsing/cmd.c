/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:31:36 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/16 03:19:07 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*check_ext(char *input, char **cp_env)
{
	int		i;
	int		j;
	char	*path;
	char	**path_split;
	char	*cmd;
	char	*tmp;

	i = 0;
	j = 0;
	path = get_env_var(cp_env, "PATH");
	if (path)
		path_split = ft_split(path, ':');
	else
		return (NULL);
	while (path_split[i])
	{
		tmp = ft_strjoin(path_split[i], "/");
		cmd = ft_strjoin(tmp, input);
		free(tmp);
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

static char	*is_built_in(char *input, char **cp_env)
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

t_tok	*check_cmd(t_tok *tok, char **cp_env)
{
	t_tok	*tmp;
	tmp = tok;
	while (tok)
	{
		if (tok->path)
		{
			if (tok->path[0] != '/')
			{
				char *in = is_built_in(tok->path, cp_env);
				char *ex = check_ext(tok->path, cp_env);
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
					ft_printf (2, "bash: %s:command not found\n", tok->path);
					return (NULL);
				}
			}
			else
			{
				if (access(tok->path, F_OK) != 0)
				{
					ft_printf (2, "Minishell: command not found: %s\n", tok->path);
					return (NULL);
				}
			}
		}
		tok = tok->next;
	}
	return (tmp);
}
