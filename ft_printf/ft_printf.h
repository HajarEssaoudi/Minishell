/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: hes-saou <hes-saou@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/11/24 00:09:49 by hes-saou          #+#    #+#             */
/*   Updated: 2024/11/24 00:09:49 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(int fd, const char *str, ...);
int	check_type(int fd, char c, va_list args);
int	ft_putchar_fd_printf(int fd, int c);
int	ft_putnbr_fd_printf(int fd, int nbr);
int	ft_putunbr_fd_printf(int fd, unsigned int nbr);
int	ft_putstr_fd_printf(int fd, char *s);
int	ft_puthex_fd_printf(int fd, char c, unsigned int nbr);
int	ft_putptr_hex_fd_printf(int fd, unsigned long n);
int	ft_putptr_fd_printf(int fd, void *ptr);
#endif