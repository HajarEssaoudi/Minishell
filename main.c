#include "minishell.h"

extern int	global;
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
void	print_str_array(char **arr)
{
	int	i;

	if (!arr)
	{
		printf("(null)\n");
		return ;
	}
	i = 0;
	while (arr[i])
	{
		printf("  [%d]: %s\n", i, arr[i]);
		i++;
	}
}

void	print_tok(t_tok *tok)
{
	int	index;

	index = 0;
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
	// exit(0);
}
int	main(int argc, char **argv, char **env)
{
	char	*l;
	t_div	*div;
	t_tok	*tok;
	char	**cp_env;
	t_tok	*tmp;

	cp_env = copy_env(env);
	signal(SIGINT, ft_hand);
	t_shell *shell = malloc(sizeof(t_shell));
	if(!shell)
	{
		//ft_clear
		exit(1);
	}
	while (1)
	{
		global = 3;
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
			tmp = tok;
			if (tok != NULL)
			{
				// printf ("%s\n", tok->execute);
				if (tok->output)
					ft_out(tok, cp_env, shell);
				else
				{
					
					tok->env = cp_env;
					tmp = tok;
					execute_cmd(tmp, tok->env, 0, shell);
				}
			}
			// free_div(div);
			// if (tok)
			// {
			// 	print_tok(tok);
			// 	free_tok(tok);
			// }
		}
		// int j = 0;
		// while (div)
		// {
		// 	printf ("type %d : %s\n", j, div->type);
		// 	j++;
		// 	div = div->next;
		// }
		// free_div(div);
		add_history(l);
		// free(l);
		// free_str(cp_env);
		// exit(1);
	}
	// free_div(div);
	return (0);
}
