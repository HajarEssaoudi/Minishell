/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:57:50 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/20 21:56:07 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
t_shell	*initialise_struct(char **env,t_shell *shell,t_tok *tok)
{
	shell = malloc(sizeof(t_shell));
	if (!shell)
	{
		ft_clear(env, shell, tok);
	}
	shell->env = create_list_env(env);
	shell->exit_status = 0;
	shell->line = 0;
	shell->pwd = NULL;
	return (shell);
}

char	**ft_exit_status(char **str, int exit)
{
	char	**tmp;
	char	*tmp1;
	char	*sub;
	char	*sub1;
	char	*exit_st;

	exit_st = ft_itoa(exit);
	int 	i;
	int		j;
	int k = 0;

	i = 0;
	while (str[k])
		k++;
	sub = NULL;
	sub1 = NULL;
	tmp1 = NULL;
	tmp = malloc(sizeof(char *) * (k + 1));
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '$' && str[i][j + 1] == '?' && !sub)
			{
				sub = ft_substr(str[i], 0, j);
				tmp1 = ft_strjoin(sub, exit_st);
				sub1 = ft_strdup(&str[i][j + 2]);
				if (sub1)
				{
					free(sub);
					sub = ft_strjoin(tmp1, sub1);
					free(tmp1);
					tmp1 = ft_strdup(sub);
				}
				j += 2;
			}
			else if (str[i][j] == '$' && str[i][j + 1] == '?' && sub)
			{
				sub1 = ft_substr(sub, 0, j);
				free(sub);
				sub = ft_strdup(sub1);
				free(sub1);
				tmp1 = ft_strjoin(sub, exit_st);
				sub1 = ft_strdup(&str[i][j + 2]);
				if (sub1)
				{
					free(sub);
					sub = ft_strjoin(tmp1, sub1);
					free(tmp1);
					tmp1 = ft_strdup(sub);
				}
				j += 2;
			}
			else
				j++;
		}
		if (tmp1)
			tmp[i] = ft_strdup(tmp1);
		else
			tmp[i] = ft_strdup(str[i]);
		i++;
	}
	tmp[i] = NULL;
	i = 0;
	free(exit_st);
	free_str(str);
	return (tmp);
}

int	main(int argc, char **argv, char **env)
{
	char	*prompt;
	char	**cp_env;
	t_tok	*tok;
	t_shell	*shell;

	signal(SIGINT, ft_handl);
	signal(SIGQUIT, SIG_IGN);
	cp_env = copy_env(env);
	shell = initialise_struct(env, shell, tok);
	while (1)
	{
		prompt = readline("Minishell$> ");
		shell->line++;
		if (!prompt)
		{
			ft_clear(cp_env, shell, tok);
			ft_printf(2, "exit\n");
			exit(shell->exit_status);
		}
		if (!prompt[0])
			continue ;
		// printf("avant exit status\n");
		tok = get_tok(prompt, cp_env);
		if (tok && tok->str)
			tok->str = ft_exit_status(tok->str, shell->exit_status);
		// printf("apres exit status\n");
		// print_tok(tok);
		if (tok != NULL)
		{
			tok->heredoc_fd = -1;
			execute_cmd(tok, shell, cp_env);
			// printf("Retour du execute_cmd\n");
			shell->pwd = get_path();
			cp_env = update_env_arr(shell->env, cp_env);
		}
		add_history(prompt);
		if (tok)
			free_tok(tok);
	}
	ft_clear(cp_env, shell, 0);
	return (0);
}
