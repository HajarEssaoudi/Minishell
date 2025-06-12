/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copie_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 09:48:51 by mabdelha          #+#    #+#             */
/*   Updated: 2025/06/12 18:49:04 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	size_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char	**copy_env(char **env)
{
	char	**cp_env;
	int		i;

	i = 0;
	cp_env = malloc(sizeof(char *) * (size_env(env) + 1));
	if (!cp_env)
	{
		free(cp_env);
		return (NULL);
	}
	while (env[i])
	{
		cp_env[i] = ft_strdup(env[i]);
		i++;
	}
	cp_env[i] = NULL;
	return (cp_env);
}
