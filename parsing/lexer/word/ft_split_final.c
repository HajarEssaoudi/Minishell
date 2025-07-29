/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_final.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 22:02:16 by abdelhaqmar       #+#    #+#             */
/*   Updated: 2025/07/30 00:16:19 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing.h"

static int	countword(char const *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t' && (i == 0 || s[i - 1] == ' ' || s[i
					- 1] == '\t'))
			count++;
		i++;
	}
	return (count);
}

static int	lenc(char const *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != ' ' && s[i] != '\t')
		i++;
	return (i);
}

static char	**free_split(char **split, int i)
{
	while (i--)
		free(split[i]);
	free(split);
	return (NULL);
}

char	**ft_split_final(char const *s)
{
	char	**split;
	int		i;
	int		j;

	i = 0;
	split = (char **)malloc((countword(s) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	while (*s)
	{
		if (*s != ' ' && *s != '\t')
		{
			split[i] = (char *)malloc(lenc(s) + 1);
			j = 0;
			if (!split[i])
				return (free_split(split, i));
			while (*s && *s != ' ' && *s != '\t')
				split[i][j++] = *s++;
			split[i++][j] = '\0';
		}
		else
			s++;
	}
	split[i] = NULL;
	return (split);
}
