#include "minishell.h"

char	*check_quot(char *input, int *index, char quot, char **cp_env)
{
    t_quot  *vars;

	vars = malloc(sizeof(t_quot));
	vars->start = *index + 1;
	vars->i = vars->start;
	vars->str = NULL;
	while (input[vars->i] && input[vars->i] != quot)
        vars->i++;
	if (input[vars->i] == quot)
	{
		if (quot == '"')
		{
			vars->sub = ft_substr(input, vars->start, vars->i - vars->start);
			vars->str = ft_var(vars->sub, cp_env, quot);
			free(vars->sub);
		}
		else
        vars->str = ft_substr(input, vars->start, vars->i - vars->start);
		*index = vars->i + 1;
	}
	else
	{
		printf("minishell: syntax error: unclosed `%c' quote\n", quot);
		return (NULL);
	}
	char	*result = vars->str;
	free(vars);
	return (result);
}
