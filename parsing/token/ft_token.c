/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:47:09 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/25 00:53:47 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

char	**ft_red(char **argv, char *arg)
{
	int		j;
	char	**argv2;
	int		i;

	j = 0;
	while (argv && argv[j])
		j++;
	argv2 = malloc(sizeof(char *) * (j + 2));
	i = 0;
	while (argv && argv[i])
	{
		argv2[i] = ft_strdup(argv[i]);
		i++;
	}
	argv2[i] = ft_strdup(arg);
	argv2[i + 1] = NULL;
	if (argv)
		free_str(argv);
	return (argv2);
}

char	**ft_argv(char **argv, char *arg)
{
	int		j;
	char	**argv2;
	int		i;

	j = 0;
	while (argv && argv[j])
		j++;
	argv2 = malloc(sizeof(char *) * (j + 2));
	i = 0;
	while (argv && argv[i])
	{
		argv2[i] = ft_strdup(argv[i]);
		i++;
	}
	argv2[i] = ft_strdup(arg);
	argv2[i + 1] = NULL;
	if (argv)
		free_str(argv);
	return (argv2);
}
