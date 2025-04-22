/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 22:37:20 by hes-saou          #+#    #+#             */
/*   Updated: 2025/04/13 22:40:51 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	fork();
	fork();
	printf("Hello everyone! My Pid = %d\n", getpid());
	// printf("Bonjour everyone\n");
	return (0);
}