#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int	main(void)
{
	int status;
	int pid = fork();
	if (pid == 0)
	{
		char *arg[] = {"ls", NULL};
		if (execve("/usr/bin/ls", arg, NULL) == -1)
			perror("execve");
	}
	else if (pid > 0)
	{
        printf("Hello\n");
		waitpid(pid, &status, 0);
	}
}
