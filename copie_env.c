/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copie_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 00:10:02 by mabdelha          #+#    #+#             */
/*   Updated: 2025/04/29 16:26:19 by hes-saou         ###   ########.fr       */
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

char	**copy_env(char **env)
{
	int		size;
	char	**cp_env;
	int		i;
	int		j;

	size = size_env(env) + 1;
	cp_env = malloc(sizeof(char *) * (size + 1));
	i = 0;
	j = 0;
	while (env[i])
	{
		cp_env[j++] = ft_strdup(env[i++]);
	}
	cp_env[j] = NULL;
	return (cp_env);
}
