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
	char	**cp_env;
	char	*l;
	t_div	*div;
	t_tok	*tok;
	t_tok	*tmp;

	cp_env = cop_env(env);
	while (1)
	{
		l = readline("Minishell$> ");
		div = ft_div(l, cp_env);
		ft_typ(div);
		tok = ft_token(div);
        tok = check_cmd(tok, cp_env);
		if (tok != NULL)
		{
			tmp = tok;
			while (tmp)
			{
				if (tmp->str && tmp->str[0])
					printf("CMD   : %s\n", tmp->str[0]);
				if (tmp->str && tmp->str[1])
					printf("OPT   : %s\n", tmp->str[1]);
				if (tmp->str && tmp->str[1])
					printf("OPT   : %s\n", tmp->str[1]);
				if (tmp->path)
					printf("PATH  : %s\n", tmp->path);
				if (tmp->output)
					printf("OUT   : %s\n", tmp->output);
				if (tmp->input)
					printf("IN    : %s\n", tmp->input);
				if (tmp->append)
					printf("APP   : %s\n", tmp->append);
				if (tmp->heredoc)
					printf("HERE  : %s\n", tmp->heredoc);
                if (tmp->filename)
					printf("FILE  : %s\n", tmp->filename);
				tmp = tmp->next;
			}
		}
		add_history(l);
		free(l);
	}
	return (0);
}
