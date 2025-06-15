#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "parsing.h"

void execute_with_pipe(t_tok *tok, char **env)
{
	int		fd[2];
	int		prev_fd = -1;
	pid_t	pid;

	while (tok)
	{
		if (tok->pip && tok->pip[0] == '|')
		{
			if (pipe(fd) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			/*not the first cmd*/
			if (prev_fd != -1)
			{
				dup2(prev_fd, 0);
				close(prev_fd);
			}

			/*not last cmd*/
			if (tok->pip && tok->pip[0] == '|')
			{
				close(fd[0]);
				dup2(fd[1], 1);
				close(fd[1]);
			}

			execve(tok->path, tok->str, env);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else
		{
			if (prev_fd != -1)
				close(prev_fd); 

			if (tok->pip && tok->pip[0] == '|')
			{
				close(fd[1]);
				prev_fd = fd[0];
			}
			else
			{
				if (prev_fd != -1)
					close(prev_fd);
				break;
			}
		}
		tok = tok->next;
	}

	// Wait for all children
	while (wait(NULL) != -1)
		;
}
