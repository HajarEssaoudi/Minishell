#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	int fd[2];
	pipe(fd);

	write(fd[1], "hello", 5); // write to pipe
	char buffer[6];
	read(fd[0], buffer, 5);   // read from pipe
	buffer[5] = '\0';
	printf("%s\n", buffer);   // prints "hello"

}