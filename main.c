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
t_div	*ft_div(char *input)
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
        		char  *str = ft_substr(input, j, i - j);
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
	char *l = readline("Minishell>> ");
	int n = 0;
	while (l)
	{
		t_div *div;
		// ft_memset(div, 0, sizeof(t_div));
		div = ft_div(l);
		t_div *tmp = div;
		while (tmp)
		{
			printf ("%s => %s\n", tmp->args, tmp->type);
			tmp = tmp->next;
		}
		
		add_history(l);

		free(l);
		l = readline("Minishell>> ");
	}
	return (0);
}