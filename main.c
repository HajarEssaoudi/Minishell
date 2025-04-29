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

int	main(int argc, char **argv, char **env)
{
	char	*l;
	t_div	*div; //hadi fiha l'input m9esem bin string rederiction
	t_tok	*tok; //hna fih dakchi m9ad w smih khrya
	t_tok	*tmp; //hadi 4ir bache noranti dakchi li 3ndi bache ndebagu
	pid_t	pid;
	int		status;
	char	**cp_env;

	cp_env = cop_env(env); //hna copite env
	while (1)
	{
		l = readline("Minishell$> ");
		div = ft_div(l, cp_env); //hna 9semt l'input lkhra lfhmti fih chi haja
		ft_typ(div); //hna kola haja 3titha type dyalha hta hiya ikhan lfhmti chi haja
		tok = ft_token(div); //hna ana w ma fehemtche ache dert fih 
		tok = check_cmd(tok, cp_env); //hna tcheket wach cmd kayna mohim il ma return null rah khdam safi nti atakhdi hada
		if (tok != NULL)
		{
			tmp = tok;
			pid = fork();
			if (pid == 0)
			{
				execute_cmd(tmp, env);
			}
			else if (pid > 0)
			{
				waitpid(pid, &status, 0);
			}
			else
			{
				perror("fork failed");
				return (1);
			}
		}
		add_history(l);
		free(l);
	}
	return (0);
}
