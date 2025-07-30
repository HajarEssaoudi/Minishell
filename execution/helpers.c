/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:00:10 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/30 21:32:52 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	is_built_in(char *input, char **cp_env)
{
	char	**cmd;
	int		i;

	cmd = (char *[]){"cd", "echo", "pwd", "export", "unset", "env", "exit",
		NULL};
	i = 0;
	if (input == NULL)
		return (0);
	while (cmd[i])
	{
		if (ft_strcmp(input, cmd[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin_env(char const *s1, char const *s2, char sep)
{
	int		i;
	int		j;
	char	*p;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	p = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1 + 1);
	if (!p)
		return (NULL);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i++] = sep;
	while (s2[j])
		p[i++] = s2[j++];
	p[i] = '\0';
	return (p);
}

int	ft_str_num(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
	{
		i++;
	}
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			i++;
		}
		else
			return (0);
	}
	return (1);
}
