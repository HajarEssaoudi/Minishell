/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:21:08 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/27 00:22:19 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static void	swap_env_nodes(t_env *a, t_env *b)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = a->key;
	tmp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = tmp_key;
	b->value = tmp_value;
}

static t_env	*sort_var(t_shell *shell)
{
	t_env	*env;
	t_env	*head;
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
				swap_env_nodes(env, env->next);
				sorted = 0;
			}
			env = env->next;
		}
	}
	return (head);
}

void	list_env_variables(t_shell *shell)
{
	t_env	*env;

	env = sort_var(shell);
	print_env(env);
}

static int	compare_and_replace(t_env *new, t_env *old)
{
	if (ft_strcmp(new->key, old->key) == 0)
	{
		free(old->value);
		old->value = new->value;
		return (1);
	}
	return (0);
}
/*ft_clear before return*/

int	execute_export(t_tok *tok, t_shell *shell)
{
	int		i;
	int		f;
	t_env	*new;
	t_env	*tmp;

	i = 1;
	f = 0;
	if (!tok->str[i])
		list_env_variables(shell);
	if (!shell->env)
	{
		ft_lstadd_back_env(&shell->env, new);
		return (0);
	}
	while (tok->str[i])
	{
		tmp = shell->env;
		while (tmp)
		{
			new = init_node_env(tok->str[i], EXPORT);
			if (!new)
				return (1);
			f = compare_and_replace(new, tmp);
			tmp = tmp->next;
		}
		if (f == 0)
			ft_lstadd_back_env(&shell->env, new);
		i++;
	}
	return (0);
}
