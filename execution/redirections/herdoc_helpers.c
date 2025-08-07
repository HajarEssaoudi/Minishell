/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:50:42 by mabdelha          #+#    #+#             */
/*   Updated: 2025/08/07 16:50:45 by mabdelha         ###   ########.fr       */
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
	i = 5;
	while (i < 15)
	{
		name[i] = characters[(unsigned char)buffer[i] % l];
		i++;
	}
	return (0);
}

void	cp_tmp(char *name)
{
	int	i;

	i = 0;
	i = 0;
	while (i < 5)
	{
		name[i] = TMP[i];
		i++;
	}
}

char	*generate_name(void)
{
	char	*name;
	int		j;
	int		i;

	name = malloc(29);
	if (!name)
		return (NULL);
	cp_tmp(name);
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
