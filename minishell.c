/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:11:00 by hes-saou          #+#    #+#             */
/*   Updated: 2025/04/13 21:19:03 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	char *line;
	char **args;
	char *cmd;
	char *pathCmd;
	while (1)
	{
		line = readline("Minishell$> ");
		printf("%s\n", line);
		// char *env[] = {NULL};

		// if (execve(av[0], &av[1], NULL) == -1)
		// {
		// 	perror("execve");
		// }
	}
	return (0);
}