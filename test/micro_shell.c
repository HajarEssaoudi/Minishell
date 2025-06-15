#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
# include <readline/readline.h>
#include <parsing.h>


int	how_many_pipes(char *line)
{
	int f = 0;
	int i = 0;
	while(line[i])
	{
		if (line[i] == '|')
			f++;
		i++;
	}
	return (f);
}

void	 execute_external_cmd(t_tok *tok, int f)
{
	char	**args;
	int		pid;
	int		status;
	int		fd1;

	pid = fork();
	if (pid == 0)
	{
		if (f > 0)
		{
			while(f != 0)
			{
				
				f--;
			}
		}
		else
		{
			if (execve(tok->path, tok->str, NULL) == -1)
			{
				perror("minishell failed");
				exit(EXIT_FAILURE);
			}
		}
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
	}
	else
	{
		perror("fork failed");
		return ;
	}
}

int main(int argc, char **argv, char **env)
{
	char	*line;
	t_tok	*tok;
	t_tok	*tmp;
	int		f;
	while(1)
	{
		line = readline("micro $>");
		f = how_many_pipes(line);
		tok = get_tok(line, tok->env);
		if (tok != NULL)
		{
			// tmp = tok;
			// print_tok(tok);
			execute_external_cmd(tok, f);
		}
	}
}