/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:31:43 by hes-saou          #+#    #+#             */
/*   Updated: 2025/06/01 17:06:53 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (2048);
	return (0);
}

int	ft_strdigit(char *str)
{
	int	i;

	i = 0;
	while(str[i])
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
