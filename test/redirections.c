#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct s_tok
{
	char *str[10];
	char *path;
	char *output[2];
}	t_tok;

int main()
{
	t_tok tok;

	tok.str[0] = "ls";
	tok.str[1] = NULL;
	tok.path = "/usr/bin/ls";
	tok.output[0] = ">";
	tok.output[1] = "file.txt";
	int fd = open(tok.output[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}

	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);

	if (execve(tok.path, tok.str, NULL) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
	return (0);
}
