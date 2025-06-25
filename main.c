/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 09:47:27 by mabdelha          #+#    #+#             */
/*   Updated: 2025/06/19 14:43:39 by hes-saou         ###   ########.fr       */
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
		int j = 0;
		while (tok->redirect)
		{
			printf("redirect #%d\n", j);
			printf("%s %s\n", tok->redirect->type, tok->redirect->filename);
			tok->redirect = tok->redirect->next;
			j++;
		}
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

t_shell	*initialise_struct(t_shell *shell, char **env)
{
	shell = malloc(sizeof(t_shell));
	if (!shell)
	{
		//ft_clear
		exit(1);
	}
	shell->env = create_list_env(env);
	return (shell);
}

void	free_list_env (t_env *env)
{
	t_env *tmp;
	while(env)
	{
		tmp = env->next;
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		free(env);
		env = tmp;
	}
	// free(env);
}

void	free_koulchi(char **cp_env,t_shell *shell, int f)
{
	if (cp_env)
		free_str(cp_env, 0);
	if (shell)
	{
		if (shell->env)
			free_list_env(shell->env);
		free(shell);
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*prompt;
	char	**cp_env;
	t_tok	*tok;
	t_tok	*tmp;
	t_shell	*shell;

	cp_env = copy_env(env);
	shell = initialise_struct(shell, cp_env);
	while (1)
	{
		prompt = readline("Minishell$> ");
		if (!prompt)
			free_str(cp_env, 1);
		// if (!prompt[0])
		// 	continue ;
		tok = get_tok(prompt, cp_env);
		// print_tok(tok);
		// print_tok(tok);
		print_tok(tok);
		// if (tok != NULL)
		// {
		// 	tmp = tok;
		// 	// print_tok(tok);
		// 	execute_cmd(tmp, cp_env, 0, shell);
		// 	cp_env = update_env_arr(shell->env, cp_env);
		// }
		add_history(prompt);
		if (tok)
			free_tok(tok);
	}
	free_koulchi(cp_env, shell, 0);
	return (0);
}
