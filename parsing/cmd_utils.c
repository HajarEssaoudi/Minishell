/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 09:44:25 by mabdelha          #+#    #+#             */
/*   Updated: 2025/08/03 09:47:15 by mabdelha         ###   ########.fr       */
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

char	*check_cmd_acces(char *input, char **path_split, char **found)
{
	char	*cmd;
	int		i;

	i = 0;
	while (path_split[i])
	{
		cmd = get_dir(input, path_split[i]);
		if (access(cmd, F_OK) == 0)
		{
			if (access(cmd, X_OK) == 0)
			{
				free_str(path_split);
				if (*found)
					free(*found);
				return (cmd);
			}
			else if (!*found)
				*found = ft_strdup(cmd);
		}
		free(cmd);
		i++;
	}
	return (NULL);
}
