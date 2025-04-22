#include "minishell.h"

void	ft_typ(t_div *div)
{
	int		st;

	st = 0;
	while (div)
	{
		if (!(ft_strncmp(div->type, "string", ft_strlen("string"))) && !st)
		{
			div->type = "cmd";
			st = 1;
		}
		else if ((st == 1 || st == 2) && !(ft_strncmp(div->type, "string",
					ft_strlen("string"))) )
		{
			div->type = "string";
			st = 2;
		}
		else if (st == 4 && !(ft_strncmp(div->type, "string",
					ft_strlen("string"))))
		{
			div->type = "filename";
			st = 3;
		}
		else if (!(ft_strncmp(div->type, "output", ft_strlen("output")))
			|| !(ft_strncmp(div->type, "input", ft_strlen("input")))
			|| !(ft_strncmp(div->type, "append", ft_strlen("append")))
			|| !(ft_strncmp(div->type, "heredoc", ft_strlen("heredoc"))))
			st = 4;
		else if (!(ft_strncmp(div->type, "pip", ft_strlen("pip"))))
			st = 0;
		div = div->next;
	}
}



t_tok	*ft_token(t_div *div)
{
	t_tok	*tok = malloc (sizeof(t_tok));
	tok->str = malloc(sizeof(char *) * 2);
	ft_memset(tok, 0, sizeof(t_tok));
	while (div)
	{
		if (!(ft_strncmp(div->type, "cmd", ft_strlen("cdm"))))
		{
			tok->path = div->args;
			tok->str[0] = div->args;
		}
		if (!(ft_strncmp(div->type, "string", ft_strlen("string"))))
		{
			tok->path = div->args;
			tok->str[0] = div->args;
		}
		if (!(ft_strncmp(div->type, "cmd", ft_strlen("cdm"))))
		{
			tok->path = div->args;
			tok->str[0] = div->args;
		}
		if (!(ft_strncmp(div->type, "cmd", ft_strlen("cdm"))))
		{
			tok->path = div->args;
			tok->str[0] = div->args;
		}
		
	}
}