/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:31:43 by hes-saou          #+#    #+#             */
/*   Updated: 2025/06/02 00:18:25 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (2048);
	return (0);
}

int	ft_str_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[0] == '+' || str[0] == '-')
			i++;
		if (ft_isdigit(str[i]))
		{
			i++;
		}
		else
			return (0);
	}
	return (1);
}
