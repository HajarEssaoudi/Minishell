#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int	main(void)
{
	int		fd[2];
	char	*args1[] = {"ls", NULL};
	char	*args2[] = {"wc", "-l", NULL};

	//ls | wc -l
	pid_t pid1, pid2;
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid1 = fork();
	if (pid1 == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1); // Redirect stdout to pipe write end, 1 ===> pipe write
		close(fd[1]);
		execve("/usr/bin/ls", args1, NULL);
		perror("execve ls");
		exit(EXIT_FAILURE);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		close(fd[1]);
		dup2(fd[0], 0); // Redirect stdin to pipe read end, 0 =====> pipe read
		close(fd[0]);
		execve("/usr/bin/wc", args2, NULL);
		perror("execve wc");
		exit(EXIT_FAILURE);
	}
	// Parent process
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
