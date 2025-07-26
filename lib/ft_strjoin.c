/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:54:07 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/24 20:17:30 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*p;

	i = 0;
	j = 0;
	if (!s1)
		return(ft_strdup(s2));
	if (!s2)
		return(ft_strdup(s1));
	p = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!p)
		return (NULL);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	while (s2[j])
		p[i++] = s2[j++];
	p[i] = '\0';
	return (p);
}

char	*ft_strjoin_sep(char const *s1, char const *s2, char sep)
{
	int		i;
	int		j;
	char	*p;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	p = (char *)malloc(i + j + 1 + 1);
	if (!p)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = sep;
	i++;
	while (s2[j])
		p[i++] = s2[j++];
	p[i] = '\0';
	return (p);
}
