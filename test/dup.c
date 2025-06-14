#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	int	fd;

	fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd, 1);
	printf("Hello, this goes into output.txt!\n");
	close(fd);
	return (0);
}
