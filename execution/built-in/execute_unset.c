/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:17:32 by hes-saou          #+#    #+#             */
/*   Updated: 2025/06/12 18:19:48 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	free_node(t_env *env)
{
	if (env)
	{
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		free(env);
	}
}

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
				free_node(tmp);
				break;
			}
			prev = tmp;
			tmp = tmp->next;
		}
		i++;
	}
}

