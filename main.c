#include "lib/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_div
{
	char			*args;
	char			*type;
	struct s_div	*next;
}					t_div;

t_div	ft_div(char *input)
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
				add_ch(&div, "pip", input[i]);
        		i++;
			}
			else
			{
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
				add_ch(&div, "redirect_out", "<<");
				i += 2;
			}
      		else
      		{
        		add_ch(&div, "redirect_out", "<");
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
	}
}
int	main(int argc, char **argv)
{
	char *l = readline(">> ");
	int n = 0;
	while (l)
	{
		t_div *div;
		ft_memset(div, 0, sizeof(t_div));
		printf("=> %s\n", l);
		add_history(l);

		free(l);
		l = readline(">> ");
	}
	return (0);
}