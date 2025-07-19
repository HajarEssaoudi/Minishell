/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:17:32 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/19 11:00:07 by hes-saou         ###   ########.fr       */
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

void	check_prev(t_env *prev, t_env *tmp, t_shell *shell)
{
	if (prev == NULL)
		shell->env = tmp->next;
	else
		prev->next = tmp->next;
}

int	execute_unset(t_tok *tok, t_shell *shell)
{
	t_env	*tmp;
	t_env	*prev;
	int		i;

	i = 1;
	if (!tok->str[i])
		return (0);
	while (tok->str[i])
	{
		tmp = shell->env;
		prev = NULL;
		while (tmp)
		{
			if (ft_strcmp(tmp->key, tok->str[i]) == 0)
			{
				check_prev(prev, tmp, shell);
				free_node(tmp);
				break ;
			}
			prev = tmp;
			tmp = tmp->next;
		}
		i++;
	}
	return (0);
}
