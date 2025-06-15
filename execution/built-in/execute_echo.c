/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:12:14 by hes-saou          #+#    #+#             */
/*   Updated: 2025/06/15 00:32:20 by hes-saou         ###   ########.fr       */
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
	if (tok->str[1])
	{
		if (tok->str[2] && ft_strcmp(tok->str[1], "-n") == 0)
		{
			print_strings(tok->str, 2);
		}
		else
		{
			print_strings(tok->str, 1);
			printf("\n");
		}
	}
	else
		printf("\n");
}
