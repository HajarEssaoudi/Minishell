/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:10:53 by hes-saou          #+#    #+#             */
/*   Updated: 2025/04/14 10:34:41 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int main()
{
	while(1)
	{
		printf("We are in the exemple1 PID = %d\n", getpid());
		fork();
		char *args[] = {"Hello", NULL};
		execv("./ex2", args);
		printf("Back to ex1\n");
	}
	return (0);
}

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	while (1)
	{
		printf("We are in exemple1 PID = %d\n", getpid());

		pid_t pid = fork();
		if (pid == 0)
		{
			// Child process
			char *args[] = {"Hello", NULL};
			execv("./ex2", args);
			// Only prints if execv fails
			perror("execv failed");
			return 1;
		}
		else if (pid > 0)
		{
			// Parent process continues the loop
			sleep(1); // To avoid spamming/fork bombing
		}
		else
		{
			perror("fork failed");
			return 1;
		}
	}
	return 0;
}
