#include "minishell.h"

extern int global;
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
void print_str_array(char **arr)
{
    if (!arr)
    {
        printf("(null)\n");
        return;
    }
    int i = 0;
    while (arr[i])
    {
        printf("  [%d]: %s\n", i, arr[i]);
        i++;
    }
}

void print_tok(t_tok *tok)
{
    int index = 0;
    while (tok)
    {
        printf("Token #%d:\n", index);
        printf(" execute: %s\n", tok->execute ? tok->execute : "(null)");
        printf(" path: %s\n", tok->path ? tok->path : "(null)");

        printf(" heredoc:\n");
        print_str_array(tok->heredoc);

        printf(" output:\n");
        print_str_array(tok->output);

        printf(" input:\n");
        print_str_array(tok->input);

        printf(" append:\n");
        print_str_array(tok->append);

        printf(" pip: %s\n", tok->pip ? tok->pip : "(null)");

        printf("------------------------\n");

        tok = tok->next;
        index++;
    }
}


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

void	ft_hand(int sig)
{
	(void)sig;
	if (global == 3)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		write (1, "\n", 1);
	}
}
int	main(int argc, char **argv, char **env)
{
	char	*l;
	t_div	*div;
	t_tok	*tok;
	char	**cp_env;

	cp_env = copy_env(env);
	// if (argc > 1)
	// {
	// 	if (file_exists(argv[1]))
	// 		execute_bash_file(argv[1]);
	// 	else
	// 		exit(1);
	// }
	// signal(SIGINT, ft_hand);
	while (1)
	{
		global = 3;
		l = readline("Minishell$> ");
		if (l[0] == '\0')
		{
			free(l);
			continue;
		}
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
			// if (tok != NULL)
			// {
			// 	// printf ("%s\n", tok->execute);
			// 	if (tok->output)
			// 		ft_out(tok, cp_env);
			// 	else
			// 	{
			// 		tok->env = cp_env;
			// 		tmp = tok;
			// 		execute_cmd(tmp, tok->env, 0);
			// 	}
			// }
			// free_div(div);
			if (tok)
			{
				print_tok(tok);
				// free_tok(tok);
			}
			
		}
		else
			free_div(div);
		add_history(l);
	}
	free(l);
	free_div(div);
	return (0);
}
