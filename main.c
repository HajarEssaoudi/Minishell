#include "minishell.h"

void	free_div(t_div *div)
{
	t_div	*tmp;

	tmp = div;
	while (div)
	{
		tmp = div;
		div = div->next;
		free(tmp->args);
		free(tmp->type);
		free(tmp);
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

int	main(int argc, char **argv, char **env)
{
	char	*l;
	t_div	*div; //hadi fiha l'input m9esem bin string rederiction
	t_tok	*tok; //hna fih dakchi m9ad
	t_tok	*tmp;
	char	**cp_env;

	cp_env = copy_env(env); //hna copite env
	if (argc > 1)
	{
		if (file_exists(argv[1]))
			execute_bash_file(argv[1]);
		else
			exit(1);
	}
	while (1)
	{
		l = readline("Minishell$> ");
		if (!l)
		{
			//ft_clear function that clears everything and exists
			exit(1);
		}
		div = ft_div(l, cp_env); //hna 9semt l'input
		ft_type(div); //hna kola haja 3titha type dyalha
		tok = ft_token(div); //hna ana w ma fehemtche ache dert fih 
		tok = check_cmd(tok, cp_env); //hna tcheket wach cmd kayna mohim il ma return null rah khdam safi nti atakhdi hada
		if (tok != NULL)
		{
			tok->env = cp_env;
			tmp = tok;
			execute_cmd(tmp, env);
		}
		add_history(l);
	}
	free(l);
	free_div(div);
	return (0);
}
