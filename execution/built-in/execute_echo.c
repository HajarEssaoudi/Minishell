/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:12:14 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/20 11:46:19 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	print_strings(char **str, int i)
{
	while (str[i])
	{
		ft_putstr_fd(str[i], 1);
		i++;
		if (str[i])
			printf(" ");
	}
}

int	check_new_line(char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (1);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	execute_echo(t_tok *tok)
{
	int	i;
	int	f;

	i = 1;
	f = 0;
	while (tok->str[i] && check_new_line(tok->str[i]) == 0)
	{
		f = 1;
		i++;
	}
	print_strings(tok->str, i);
	if (!f)
		printf("\n");
	return (0);
}
