/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:12:14 by hes-saou          #+#    #+#             */
/*   Updated: 2025/06/15 22:20:39 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	print_strings(char **str, int i)
{
	while (str[i])
	{
		printf("%s", str[i]);
		i++;
		if (str[i])
			printf(" ");
	}
}

void	execute_echo(t_tok *tok)
{
	int		i;
	int		f_option;

	i = 1;
	if (!tok->str[1])
	{
		printf("\n");
		return ;
	}
	while (tok->str[i])
	{
		if (ft_strncmp(tok->str[i], "-n", 2) == 0)
			i++;
		else
			break;
	}
	if (tok->str[i])
		print_strings(tok->str, i);
}
