/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:57:50 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/10 00:22:12 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		printf("herdoc_fd == %d\n", tok->heredoc_fd);
		int j = 0;
		while (tok->redirect)
		{
			printf("redirect #%d\n", j);
			printf("%s %s\n", tok->redirect->type, tok->redirect->filename);
			tok->redirect = tok->redirect->next;
			j++;
		}
		printf(" pip: %s\n", tok->pip ? tok->pip : "(null)");
		printf("------------------------\n");
		tok = tok->next;
		index++;
	}
}

t_shell	*initialise_struct(char **env,t_shell *shell,t_tok *tok)
{
	shell = malloc(sizeof(t_shell));
	if (!shell)
	{
		ft_clear(env, shell, tok);
	}
	shell->env = create_list_env(env);
	return (shell);
}

int	main(int argc, char **argv, char **env)
{
	char	*prompt;
	char	**cp_env;
	t_tok	*tok;
	t_shell	*shell;

	cp_env = copy_env(env);
	shell = initialise_struct(env, shell, tok);
	while (1)
	{
		prompt = readline("Minishell$> ");
		if (!prompt)
		{
			ft_clear(cp_env, shell, tok);
			ft_printf(2, "exit\n");
			shell->exit_status = EXIT_SUCCESS;
			exit(shell->exit_status);
		}
		if (!prompt[0])
			continue ;
		tok = get_tok(prompt, cp_env);
		if (tok != NULL)
		{
			tok->heredoc_fd = -1;
			print_tok(tok);
			execute_cmd(tok, shell, cp_env);
			cp_env = update_env_arr(shell->env, cp_env);
		}
		printf("exit status:%d\n", shell->exit_status);
		add_history(prompt);
		if (tok)
			free_tok(tok);
	}
	ft_clear(cp_env, shell, 0);
	return (0);
}
