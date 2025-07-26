/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 00:11:02 by mabdelha          #+#    #+#             */
/*   Updated: 2025/07/24 01:54:13 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing.h"

char	*get_env_var(char **cp_env, char *var)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(var);
	while (cp_env[i])
	{
		if (ft_strncmp(cp_env[i], var, len) == 0 && cp_env[i][len] == '=')
			return (&cp_env[i][len + 1]);
		i++;
	}
	return (NULL);
}

char	*ft_var(char *str, char **cp_env)
{
	char	*var;

	var = get_env_var(cp_env, str);
	return (var);
}
