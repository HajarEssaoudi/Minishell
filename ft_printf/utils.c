/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 00:10:06 by hes-saou          #+#    #+#             */
/*   Updated: 2025/06/04 16:47:33 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_fd(int fd, int c)
{
	int	count;

	count = 0;
	count += write(fd, &c, 1);
	return (count);
}

int	ft_putstr_fd(int fd, char *s)
{
	int	count;

	count = 0;
	if (!s)
		return (ft_putstr_fd(fd, "(null)"));
	while (*s)
	{
		write(fd, s, 1);
		s++;
		count++;
	}
	return (count);
}

int	ft_putnbr_fd(int fd, int nbr)
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
		count += ft_putnbr_fd(fd, n / 10);
	digit = (n % 10) + '0';
	count += write(fd, &digit, 1);
	return (count);
}

int	ft_putunbr_fd(int fd, unsigned int n)
{
	char	digit;
	int		count;

	count = 0;
	if (n >= 10)
		count += ft_putunbr_fd(fd, n / 10);
	digit = (n % 10) + '0';
	count += write(fd, &digit, 1);
	return (count);
}
