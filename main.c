#include "minishell.h"

// void	free_div(t_div *div)
// {
// 	t_div	*tmp;

// 	tmp = div;
// 	while (div)
// 	{
// 		tmp = div;
// 		div = div->next;
// 		free(tmp->args);
// 		free(tmp->type);
// 		free(tmp);
// 	}
// }

int	file_exists(char *filename)
{
	if(access(filename, F_OK) == 0)
		return (1);
	else
	{
		ft_putstr_fd("Minishell: No such file or directory\n", 2);
		return (0);
	}
}

void	execute_bash_file(char *filename)
{
	char *args[] = {"/bin/bash", filename, NULL};
	if (execve("/bin/bash", args, NULL) == -1)
		perror("execve failed");
}

void	ft_hand(int sig, int i)
{
	(void)sig;
	write(1, "\n", 1);
	i = 1;
}
int	main(int argc, char **argv, char **env)
{
	char	*l;
	t_div	*div;
	t_tok	*tok;
	char	**cp_env;

	cp_env = copy_env(env);
	if (argc > 1)
	{
		if (file_exists(argv[1]))
			execute_bash_file(argv[1]);
		else
			exit(1);
	}
	while (1)
	{
		int i = 0;
		signal(SIGINT, ft_hand);
		if (i)
		{
			i = 0;
			continue;
		}
		l = readline("Minishell$> ");
		if (l[0] == '\0')
			continue;
		if (!l)
		{
			printf("exit\n");
			exit(1);
		}
		
		
		div = ft_div(l, cp_env);
		if (div)
		{
			ft_type(div);
			tok = ft_token(div);
			tok = check_cmd(tok, cp_env);
			t_tok *tmp = tok;
			if (tok != NULL)
			{
				// printf ("%s\n", tok->execute);
				if (tok->output)
					ft_out(tok, cp_env);
				else
				{
					tok->env = cp_env;
					tmp = tok;
					execute_cmd(tmp, tok->env);
				}
			}
			// free_div(div);
		}
		else
			free_div(div);
		add_history(l);
	}
	free(l);
	free_div(div);
	return (0);
}
