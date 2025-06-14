#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	char	fd[2];
	pid_t	pid1, pid2;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	pid1 = fork();
	if (pid1 == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		
	}
	pid2 = fork();
	if (pid2 == 0)
	{

	}
}