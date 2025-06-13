/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:21:08 by hes-saou          #+#    #+#             */
/*   Updated: 2025/06/13 10:26:58 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_env	*sort_var(t_shell *shell)
{
	t_env	*env;
	t_env	*head;
	char	*tmp_key;
	char	*tmp_value;
	int		sorted;

	head = shell->env;
	if (!head)
		return (NULL);
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		env = head;
		while (env && env->next)
		{
			if (ft_strcmp(env->key, env->next->key) > 0)
			{
				tmp_key = env->key;
				tmp_value = env->value;
				env->key = env->next->key;
				env->value = env->next->value;
				env->next->key = tmp_key;
				env->next->value = tmp_value;
				sorted = 0;
			}
			env = env->next;
		}
	}
	return (head);
}

void print_env(t_env *env)
{
	int i;
	t_env *tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

void	list_env_variables(t_shell *shell)
{
	t_env	*env;

	env = sort_var(shell);
	print_env(env);
}

void	execute_export(t_tok *tok, t_shell *shell)
{
	int		i;
	t_env	*new;
	t_env	*tmp;

	i = 1;
	if (!tok->str[i])
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
