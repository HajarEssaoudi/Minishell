/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in_extra.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:17:41 by hes-saou          #+#    #+#             */
/*   Updated: 2025/06/04 16:28:23 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_unset(t_tok *tok, t_shell *shell)
{
	t_env	*tmp;
	t_env	*prev;
	int		i;

	i = 1;
	if (!tok->str[i])
		return;
	while (tok->str[i])
	{
		tmp = shell->env;
		prev = NULL;
		while (tmp)
		{
			if (ft_strcmp(tmp->key, tok->str[i]) == 0)
			{
				if (prev == NULL)
					shell->env = tmp->next;
				else
					prev->next = tmp->next;
				free(tmp->key);
				free(tmp->value);
				free(tmp);
				break;
			}
			prev = tmp;
			tmp = tmp->next;
		}
		i++;
	}
}

void	execute_export(t_tok *tok, t_shell *shell)
{
	int		i;
	t_env	*new;
	t_env	*tmp;

	i = 1;
	if (!tok->str[1])
		list_env_variables(shell);
	while(tok->str[i])
	{
		tmp = shell->env;
		while (tmp)
		{
			new = init_node_env(tok->str[i]);
			if (ft_strcmp(new->key , tmp->key) == 0)
			{
				free(tmp->value);
				tmp->value = new->value;
				return ;
			}
			tmp = tmp->next;
		}
		ft_lstadd_back_env(&shell->env, new);
		i++;
	}
}

void	execute_echo(t_tok *tok)
{
	if (tok->str[1])
	{
		if (tok->str[2] && ft_strcmp(tok->str[1], "-n") == 0)
		{
			print_strings(tok->str, 2);
		}
		else
		{
			print_strings(tok->str, 1);
			printf("\n");
		}
	}
	else
		printf("\n");
}

void	execute_exit(t_tok *tok, t_shell *shell)
{
	shell->exit_status = 0;
	if (tok->str[1])
	{
		if (ft_atoi(tok->str[1]) >= LONG_MAX)
		{
			shell->exit_status = 2;
			printf("exit\n");
			//ft_clear
			printf("Minishell: exit: %s: numeric argument required\n", tok->str[1]);
			exit(shell->exit_status);
		}
		if (!ft_str_num(tok->str[1]))
		{
			shell->exit_status = 2;
			printf("exit\n");
			//ft_clear
			printf("Minishell: exit: %s: numeric argument required\n", tok->str[1]);
			exit(shell->exit_status);
		}
		else if (ft_str_num(tok->str[1]))
		{
			if (tok->str[2])
			{
				printf("exit\n");
				shell->exit_status = 1;

				ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
			}
			else if (!tok->str[2])
			{
				shell->exit_status = (unsigned char)ft_atoi(tok->str[1]);
				printf("exit\n");
				//ft_clear
				exit(shell->exit_status);
			}
		}
	}
	else if (!tok->str[1])
	{
		// ft_clear
		printf("exit\n");
		exit(shell->exit_status);
	}
}
