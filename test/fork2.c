#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int ac, char **av)
{
	int status;
	int pid = fork();
	int n = 0;
	if (pid == 0)
		n = 1;
	else
		n = 6;
	if (pid != 0)
		wait(&status);
	int i;
	for (i = n; i < n + 5; i++)
	{
		printf("%d ", i);
		fflush(stdout);
	}
	if (pid != 0)
		printf("\n");
	return 0;
}