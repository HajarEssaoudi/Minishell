/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:57:50 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/29 03:44:47 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../execution/execution.h"

int	g_flag = 0;

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
		printf ("quot => %d\n", tok->quot);
		int j = 0;
		while (tok->redirect)
		{
			printf("redirect #%d\n", j);
			printf("%s %s %s\n", tok->redirect->type, tok->redirect->filename, tok->redirect->flag);
			tok->redirect = tok->redirect->next;
			j++;
		}
		printf(" pip: %s\n", tok->pip ? tok->pip : "(null)");
		printf("------------------------\n");
		tok = tok->next;
		index++;
	}
}
t_shell	*initialise_struct(char **env, t_shell *shell, t_tok *tok)
{
	shell = malloc(sizeof(t_shell));
	if (!shell)
	{
		ft_clear(env, shell, tok);
	}
	shell->env = create_list_env(env);
	// if (!shell->env)
	// 	return (NULL);
	shell->exit_status = 0;
	shell->saved_stdout = 0;
	shell->saved_stdin = 0;
	shell->line = 0;
	shell->pwd = NULL;
	return (shell);
}

int	main(int argc, char **argv, char **env)
{
	char	*prompt;
	char	**cp_env;
	t_tok	*tok;
	(void)argc;
	(void)argv;
	t_shell	*shell;

	signal(SIGINT, ft_handl);
	signal(SIGQUIT, SIG_IGN);
	cp_env = copy_env(env);
	tok = NULL;
	shell = NULL;
	shell = initialise_struct(env, shell, tok);
	if (!shell)
		return (1);
	while (1)
	{
		prompt = readline("Minishell$> ");
		shell->line++;
		if (!prompt)
		{
			int	status = shell->exit_status;
			ft_clear(cp_env, shell, tok);
			ft_printf(2, "exit\n");
			exit(status);
		}
		if (!prompt[0])
			continue ;
		tok = get_tok(prompt, cp_env, shell->exit_status);
		if (!tok)
			shell->exit_status = 2;
		// print_tok(tok);
		if (tok != NULL)
		{
			tok->heredoc_fd = -1;
			int is_pipeline = 0;
            t_tok *tmp = tok;
            while (tmp)
            {
                if (tmp->pip && tmp->pip[0] == '|')
                {
                    is_pipeline = 1;
                    break;
                }
                tmp = tmp->next;
            }
			execute_cmd(tok, shell, cp_env);
			if (shell->pwd)
				free(shell->pwd);
			shell->pwd = get_path();
			cp_env = update_env_arr(shell->env, cp_env);
			if (!is_pipeline)
				free_tok(tok);
		}
		add_history(prompt);
		free(prompt);
	}
	// ft_clear(cp_env, shell, 0);
	return (0);
}
