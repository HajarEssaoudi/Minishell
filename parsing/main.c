/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 09:47:27 by mabdelha          #+#    #+#             */
/*   Updated: 2025/06/12 18:49:53 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
		print_str_array(tok->str);
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

int	main(int argc, char **argv, char **env)
{
	char	*prompt;
	char	**cp_env;
	t_tok	*tok;

	cp_env = copy_env(env);
	while (1)
	{
		prompt = readline("Minishell$> ");
		if (!prompt[0])
			continue ;
		if (!prompt)
		{
			free_str(cp_env);
			printf("exit\n");
			exit(1);
		}
		tok = get_tok(prompt, cp_env);
	}
	free_str(cp_env);
	return (0);
}
