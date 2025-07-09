/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 00:10:06 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/09 10:59:26 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_fd_printf(int fd, int c)
{
	int	count;

	count = 0;
	count += write(fd, &c, 1);
	return (count);
}

int	ft_putstr_fd_printf(int fd, char *s)
{
	int	count;

	count = 0;
	if (!s)
		return (ft_putstr_fd_printf(fd, "(null)"));
	while (*s)
	{
		write(fd, s, 1);
		s++;
		count++;
	}
	return (count);
}

int	ft_putnbr_fd_printf(int fd, int nbr)
{
	long	n;
	char	digit;
	int		count;

	n = nbr;
	count = 0;
	if (n < 0)
	{
		count += write(fd, "-", 1);
		n = -n;
	}
	if (n >= 10)
		count += ft_putnbr_fd_printf(fd, n / 10);
	digit = (n % 10) + '0';
	count += write(fd, &digit, 1);
	return (count);
}

int	ft_putunbr_fd_printf(int fd, unsigned int n)
{
	char	digit;
	int		count;

	count = 0;
	if (n >= 10)
		count += ft_putunbr_fd_printf(fd, n / 10);
	digit = (n % 10) + '0';
	count += write(fd, &digit, 1);
	return (count);
}
