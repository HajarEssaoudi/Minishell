/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:47:09 by hes-saou          #+#    #+#             */
/*   Updated: 2025/04/29 16:47:20 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_type(t_div *div)
{
	int		st;

	st = 0;
	while (div)
	{
		if (!(ft_strncmp(div->type, "string", ft_strlen("string"))) && (!st || st == 3))
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

char	**ft_argv(char **argv, char *arg)
{
	int j = 0;
	while (argv && argv[j])
		j++;
	char	**argv2 = malloc(sizeof(char *) * (j + 2));

	int i = 0;
	while (argv && argv[i])
	{
		argv2[i] = ft_strdup(argv[i]);
		i++;
	}
	argv2[i] = ft_strdup(arg);
	argv2[i + 1] = NULL;
	if (argv)
		free(argv);
	return (argv2);
}

t_tok	*ft_token(t_div *div)
{
	t_tok	*tok = malloc(sizeof(t_tok));
	ft_memset(tok, 0, sizeof(t_tok));
	t_tok	*tmp = tok;
	//hi ty9tini ma 3arfche 3arfek hagrani wlkn machi mochkil met3i 3inik wlh la chreht
	while (div)
	{
		if (!(ft_strncmp(div->type, "cmd", ft_strlen("cmd"))))
		{
			tmp->path = div->args;
			tmp->str = ft_argv(tmp->str, div->args);
		}
		if (!(ft_strncmp(div->type, "string", ft_strlen("string"))))
		{
			tmp->str = ft_argv(tmp->str, div->args);
		}
		if (!(ft_strncmp(div->type, "filename", ft_strlen("filename"))))
		{
			tmp->filename = div->args;
		}
		if (!(ft_strncmp(div->type, "output", ft_strlen("output"))))
			tmp->output = div->args;
		if (!(ft_strncmp(div->type, "input", ft_strlen("input"))))
			tmp->input = div->args;
		if (!(ft_strncmp(div->type, "append", ft_strlen("append"))))
			tmp->append = div->args;
		if (!(ft_strncmp(div->type, "heredoc", ft_strlen("heredoc"))))
			tmp->heredoc = div->args;
		if (!(ft_strncmp(div->type, "pip", ft_strlen("pip"))))
		{
			tmp->next = malloc(sizeof(t_tok));
			ft_memset(tmp->next, 0, sizeof(t_tok));
			tmp = tmp->next;
		}
		div = div->next;
	}
	return (tok);
}
