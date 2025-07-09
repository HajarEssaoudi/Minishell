/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 23:06:18 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/09 10:59:09 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex_fd_printf(int fd, char c, unsigned int n)
{
	char	*base_small;
	char	*base_upp;
	int		count;

	count = 0;
	base_small = "0123456789abcdef";
	base_upp = "0123456789ABCDEF";
	if (n >= 16)
		count += ft_puthex_fd_printf(fd, c, n / 16);
	if (c == 'x')
		count += ft_putchar_fd_printf(fd, base_small[n % 16]);
	else if (c == 'X')
		count += ft_putchar_fd_printf(fd, base_upp[n % 16]);
	return (count);
}

int	ft_putptr_hex_fd_printf(int fd, unsigned long n)
{
	char	*base;
	int		count;

	count = 0;
	base = "0123456789abcdef";
	if (n >= 16)
		count += ft_putptr_hex_fd_printf(fd, n / 16);
	count += ft_putchar_fd_printf(fd, base[n % 16]);
	return (count);
}

int	ft_putptr_fd_printf(int fd, void *ptr)
{
	int	count;

	count = 0;
	if (!ptr)
		return (ft_putstr_fd_printf(fd, "(nil)"));
	count += ft_putstr_fd_printf(fd, "0x");
	count += ft_putptr_hex_fd_printf(fd, (unsigned long)ptr);
	return (count);
}
