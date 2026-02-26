/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:04:22 by hes-saou          #+#    #+#             */
/*   Updated: 2024/11/28 19:04:22 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(int fd, const char *str, ...)
{
	va_list	args;
	int		i;
	int		count;

	i = 0;
	count = 0;
	va_start(args, str);
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (str[i + 1] == '\0')
				return (-1);
			else
			{
				count += check_type(fd, str[i + 1], args);
				i += 2;
			}
		}
		else
			count += ft_putchar_fd(fd, str[i++]);
	}
	return (count);
}

int	check_type(int fd, char c, va_list args)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += ft_putchar_fd(fd, va_arg(args, int));
	else if (c == 's')
		count += ft_putstr_fd(fd, va_arg(args, char *));
	else if (c == 'd' || c == 'i')
		count += ft_putnbr_fd(fd, va_arg(args, int));
	else if (c == 'u')
		count += ft_putunbr_fd(fd, va_arg(args, int));
	else if (c == 'x' || c == 'X')
		count += ft_puthex_fd(fd, c, va_arg(args, int));
	else if (c == 'p')
		count += ft_putptr_fd(fd, va_arg(args, void *));
	else if (c == '%')
		count += ft_putchar_fd(fd, '%');
	return (count);
}
