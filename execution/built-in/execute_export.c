/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:21:08 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/08 01:53:44 by hes-saou         ###   ########.fr       */
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

static void	print_env(t_env *env)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

static void	list_env_variables(t_shell *shell)
{
	t_env	*env;

	env = sort_var(shell);
	print_env(env);
}

static void	compare_end_replace(t_env *new, t_env *old)
{
	if (ft_strcmp(new->key, old->key) == 0)
	{
		free(old->value);
		old->value = new->value;
		return ;
	}
}
/*ft_clear before return*/

void	execute_export(t_tok *tok, t_shell *shell)
{
	int		i;
	t_env	*new;
	t_env	*tmp;

	i = 1;
	if (!tok->str[i])
		list_env_variables(shell);
	while (tok->str[i])
	{
		tmp = shell->env;
		while (tmp)
		{
			new = init_node_env(tok->str[i]);
			if (!new)
			{
				return ;
			}
			compare_end_replace(new, tmp);
			tmp = tmp->next;
		}
		ft_lstadd_back_env(&shell->env, new);
		i++;
	}
}
