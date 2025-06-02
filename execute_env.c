/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:19:31 by hes-saou          #+#    #+#             */
/*   Updated: 2025/06/02 15:16:14 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *init_node_env(char *str_env)
{
	t_env	*node_env;
	char	*equal;

	node_env = malloc(sizeof(t_env));
	if(!node_env)
	{
		ft_putstr_fd("allocation failed\n", 2);
		//clear_exit;
	}
	equal = ft_strchr(str_env, '=');
	if (equal)
	{
		node_env->key = ft_substr(str_env, 0, (equal - str_env + 1));
		node_env->value = ft_strdup(equal + 1);
	}
	else
	{
		return (NULL);
	}
	return (node_env);
}

t_env *create_list_env(char **arr_env)
{
	t_env	*head;
	t_env	*tmp;
	int		i;

	i = 0;
	head = NULL;
	tmp = NULL;
	while(arr_env[i])
	{
		t_env *new_node = init_node_env(arr_env[i]);
		if (new_node == NULL)
		{
			ft_putstr_fd("allocation failed\n", 2);
			//clear_exit
		}
		if (!head)
			head = new_node;
		else
			tmp->next = new_node;
		tmp = new_node;
		i++;
	}
	return (head);
}
