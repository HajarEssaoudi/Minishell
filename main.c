#include "lib/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_div
{
	char			*args;
	char			*type;
	struct s_div	*next;
}					t_div;

int size_env(char **env)
{
  int i = 0;
  while (env[i])
    i++;
  return i;
}

char *get_env_var(char **cp_env, char *key)
{
    int i = 0;
    size_t len = ft_strlen(key);
    while (cp_env[i])
    {
        if (ft_strncmp(cp_env[i], key, len) == 0 && cp_env[i][len] == '=')
            return &cp_env[i][len + 1];
        i++;
    }
    return NULL;
}

char **cop_env(char **env)
{
  int size = size_env(env) + 1;
  char **cp_env = malloc(sizeof(char *) * size);

  int i = 0;
  int j = 0;
  while (env[i])
  {
    cp_env[j++] = ft_strdup(env[i++]);
  }
  cp_env[j] = NULL;
  return cp_env;
}

char    *cv_var(char *str)
{
    int i = 0;
    while(str[i] != '$')
        i++;
    i++;
    while (str[i] && (str[i] == '~' || str[i] == '=' || str[i] == '^'))
        i++;
    if (str[i] && !(ft_isdigit(str[i])))
    {
        int j = i;
        while ((ft_isalpha(str[i]) || str[i] == '_') && str[i])
            i++;
        char *var = ft_substr(str, j, i - j);
        return var;
    }
	else if (str[i] && ft_isdigit(str[i]))
		return ("1");
    return NULL;
}

char    *ft_var(char *str, char **cp_env)
{
	char *key = cv_var(str);
	char *var = NULL;
	if (key != NULL && key != "1")
    	var = get_env_var(cp_env, key);

    char *g_var;
    int s = ft_strlen(str) + 1;
    int i = 0;
    int j = 0;
    if (var != NULL)
    {
        while (str[i] && str[i] != '$')
            i++;
        while (str[i] && str[i] != ' ')
        {
            i++;
            j++;
        }
        int v = (s - j) + ft_strlen(var);
        g_var = malloc (sizeof(char *) * v);
    }
    else
        g_var = malloc (sizeof(char *) * s);
    i = 0;
    j = 0;
    while (str[i])
    {
		if (str[i] != '$')
			g_var[j++] = str[i++];
        else if (var != NULL)
        {
            while (str[i] && str[i] != '$')
                g_var[j++] = str[i++];
            int k = 0;
            while (var[k])
                g_var[j++] = var[k++];
            while (str[i] && (str[i] != ' ' && str[i] != '-'))
                i++;
			
        }
		else if (key == "1")
		{
			while(str[i] != '$')
        		i++;
   			 i++;
   			 while (str[i] && (str[i] == '~' || str[i] == '=' || str[i] == '^'))
        		i++;
			while (str[i] >= '0' && str[i] <= '9')
				i++;
			key = 0;
		}
    }
    return g_var;
}

void check_redirect(char *input)
{
	if (input[0] == '>' && input[1] == '>')
	{
		printf("zsh: parse error near '>>'\n");
		exit(1);
	}
	else if (input[0] == '<' && input[1] == '<')
	{
		printf("zsh: parse error near '<<'\n");
		exit(1);
	}
	int i = 0;
	while (input[i])
	{
		if (input[i] == '>' && input[i + 1] == '>')
			i += 2;
		else if (input[i] == '<' && input[i + 1] == '<')
			i += 2;
		else if (input[i] == '>' && input[i + 1] != '>')
			i++;
		else if (input[i] == '<' && input[i + 1] != '<')
			i++;
		while (input[i] == ' ')
			i++;
		if (input[i] == '>' && input[i + 1] != '>')
		{
			printf("zsh: parse error near '>'\n");
			exit(1);
		}
		else if (input[i] == '>' && input[i + 1] == '>')
		{
			printf("zsh: parse error near '>>'\n");
			exit(1);
		}
		if (input[i] == '<' && input[i + 1] != '<')
		{
			printf("zsh: parse error near '<'\n");
			exit(1);
		}
		else if (input[i] == '<' && input[i + 1] == '<')
		{
			printf("zsh: parse error near '<<'\n");
			exit(1);
		}
		i++;
	}
}
// void get_variable(char *str)
// {
// 	char *v = NULL;
// 	int i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 		{
// 			int j = ++i;
// 			while (str[i] && str[i] != '>' && str[i] != '<' && str[i] != '|' && str[i] != ' ')
//         		i++;
// 			v = ft_substr(str, j, i - j);
// 		}
// 		i++;
// 	}
	
// 	char *var = getenv(v);
// 	printf ("%s", var);
// 	return;
// }
void	add_ch(t_div **div, char *type, char *input)
{
	t_div *token = malloc(sizeof(t_div));
	t_div *tmp;

	token->args = ft_strdup(input);
	token->type = ft_strdup(type);
	token->next = NULL;
	if (!*div)
		*div = token;
	else
	{
		tmp = *div;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = token;
	}
}

t_div	*ft_div(char *input, char **cp_env)
{
	int		i;
	t_div	*div;

	i = 0;
	div = NULL;
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (!input[i])
			exit(1);
		if (input[i] == '|')
		{
			if (i > 1 && input[i - 1] != ' ')
			{
				add_ch(&div, "pip", "|");
        		i++;
			}
			else
			{
				// perror("pipe");
        		printf("zsh: parse error near '|'\n");
        		exit(1);
      		}
		}
		else if (input[i] == '>')
		{
			if (input[i + 1] == '>')
			{
				add_ch(&div, "redirect_out", ">>");
				i += 2;
			}
      		else
      		{
        		add_ch(&div, "redirect_out", ">");
				i++;
      		}
		}
    	else if (input[i] == '<')
		{
			if (input[i + 1] == '<')
			{
				add_ch(&div, "redirect_in", "<<");
				i += 2;
			}
      		else
      		{
        		add_ch(&div, "redirect_in", "<");
				i++;
      		}
		}
    	else if (input[i] == '"' || input[i] == '\'')
    	{
      		char  q = input[i];
      		int j = ++i;
      		while (input[i] && input[i] != q)
        		i++;
      		if (input[i] && input[i] == q)
      		{
        		char  *str;
				if (q == '"')
				{
					str = ft_strdup(ft_var(ft_substr(input, j, i - j), cp_env));
				}
				else
					str = ft_substr(input, j, i - j);
				add_ch(&div, "string", str);
				free(str);
				i++;
	  		}
	  		else
	  		{
				printf("zsh: parse error near '%c'\n", q);
				exit(1);
      		}	
    	}
		else
    	{
      		int j = i;
      		while (input[i] && input[i] != '>' && input[i] != '<' && input[i] != '|' && input[i] != ' ')
        		i++;
      		if (input[i])
      		{
        		char  *str = ft_substr(input, j, i - j);
				add_ch(&div, "string", str);
				free(str);
				i++;
	  		}
    	}
	}
	return	div;
}
int	main(int argc, char **argv, char **env)
{
	char **cp_env = cop_env(env);
	while (1)
	{
		char *l = readline("Minishell>> ");
		t_div *div;
		// ft_memset(div, 0, sizeof(t_div));
		div = ft_div(l, cp_env);
		t_div *tmp = div;
		while (tmp)
		{
			printf ("%s => %s\n", tmp->args, tmp->type);
			// get_variable(tmp->args);
			tmp = tmp->next;
		}
		add_history(l);

		free(l);
	}
	return (0);
}