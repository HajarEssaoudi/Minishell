#include <stdio.h>
#include <stdlib.h>
# include <ctype.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
#include <limits.h>

void	main ()
{
	pid_t	pid;
	int		status;

	char *args[] = {"ls", "ls", NULL};
	pid = fork();
	if (pid == 0)
	{
		if (execve("ls",args, NULL) == -1)
		{
			perror("minishell failed");
			exit(1);
		}
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
	{
		perror("fork failed");
		return ;
	}
}