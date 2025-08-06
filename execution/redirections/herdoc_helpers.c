/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 04:38:44 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/06 04:38:46 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	random_name(char *name, char *characters)
{
	int		fd;
	char	buffer[15];
	int		l;
	int		i;

	l = ft_strlen(characters);
	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		return (-1);
	if (read(fd, buffer, 15) != 15)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	i = 0;
	while (i < 15)
	{
		name[i] = characters[(unsigned char)buffer[i] % l];
		i++;
	}
	return (0);
}

char	*her_name(void)
{
	char	*name;
	int		j;
	int		i;

	name = malloc(24);
	if (!name)
		return (NULL);
	if (random_name(name, CHARACTER) < 0)
	{
		free(name);
		return (NULL);
	}
	i = 15;
	j = 0;
	while (j < 8)
	{
		name[i++] = EXTENSION[j];
		j++;
	}
	name[i] = '\0';
	return (name);
}
