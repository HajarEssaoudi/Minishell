/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:57:50 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/07 09:45:58 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*initialise_struct(char **env, t_shell *shell, t_tok *tok)
{
	shell = malloc(sizeof(t_shell));
	if (!shell)
	{
		ft_clear(env, shell);
	}
	shell->env = create_list_env(env, tok, shell);
	shell->exit_status = 0;
	shell->saved_stdout = 0;
	shell->saved_stdin = 0;
	shell->current_path = get_path();
	shell->old_path = NULL;
	shell->arr_env = NULL;
	return (shell);
}

void	handle_ctrl_d(t_shell *shell, char **env)
{
	int	status;

	status = shell->exit_status;
	ft_clear(env, shell);
	if (isatty(STDIN_FILENO))
		write(2, "exit\n", 6);
	exit(status);
}

void	minishell_loop(t_shell *shell, char **cp_env, t_tok *tok)
{
	char	*prompt;
	t_tok	*tmp;

	while (1)
	{
		prompt = readline("Minishell$> ");
		if (!prompt)
			handle_ctrl_d(shell, cp_env);
		if (!prompt[0])
			continue ;
		tok = get_tok(prompt, cp_env, shell->exit_status);
		if (!tok)
			shell->exit_status = 2;
		if (tok != NULL)
		{
			tok->heredoc_fd = -1;
			tmp = tok;
			execute_cmd(tmp, shell, cp_env);
			cp_env = update_env_arr(shell->env, cp_env);
			if (!tok->pip)
				free_tok(tok);
		}
		add_history(prompt);
		free(prompt);
	}
}

int	main(int argc, char **argv, char **env)
{
	char	**cp_env;
	t_tok	*tok;
	t_shell	*shell;

	(void)argc;
	(void)argv;
	tok = NULL;
	shell = NULL;
	signal(SIGINT, ft_handle);
	signal(SIGQUIT, SIG_IGN);
	cp_env = copy_env(env);
	shell = initialise_struct(env, shell, tok);
	if (!shell)
		return (1);
	minishell_loop(shell, cp_env, tok);
	return (0);
}
