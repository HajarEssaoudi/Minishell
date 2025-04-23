/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copie_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-23 00:10:02 by mabdelha          #+#    #+#             */
/*   Updated: 2025-04-23 00:10:02 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char	**cop_env(char **env)
{
	int		size;
	char	**cp_env;
	int		i;
	int		j;

	size = size_env(env) + 1;
	cp_env = malloc(sizeof(char *) * size);
	i = 0;
	j = 0;
	while (env[i])
	{
		cp_env[j++] = ft_strdup(env[i++]);
	}
	cp_env[j] = NULL;
	return (cp_env);
}
