/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:13:40 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/20 11:46:39 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	execute_env(t_tok *tok, char **env)
{
	int	i;

	i = 0;
	if (tok->str[1])
	{
		ft_printf(2, "env: too many arguments\n");
		return (EXIT_NOT_FOUND);
	}
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
