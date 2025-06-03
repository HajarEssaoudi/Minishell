/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:19:31 by hes-saou          #+#    #+#             */
/*   Updated: 2025/06/02 17:24:24 by hes-saou         ###   ########.fr       */
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
		node_env->key = ft_substr(str_env, 0, (equal - str_env));
		node_env->value = ft_strdup(equal + 1);
	}
	else
	{
		return (NULL);
	}
	return (node_env);
}

void print_list(t_env *env)
{
	int i;
	t_env *tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		printf("key == %s\n", tmp->key);
		tmp = tmp->next;
	}
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

int	ft_lst_size(t_env *lst)
{
	t_env	*tmp;
	int		count;

	tmp = lst;
	count = 0;
	while (tmp)
	{
		tmp = tmp->next;
		count++;
	}
	return (count);
}

char	**update_env_arr(t_env *lst_env, char **arr_env)
{
	int	i;

	i = 0;
	free_str(arr_env);
	arr_env = malloc(sizeof(char *) * (ft_lst_size(lst_env) + 1));
	while (lst_env)
	{
		// arr_env[i] = ft_strdup(lst_env->key);
		arr_env[i] = ft_strjoin(lst_env->key, "=");
		arr_env[i] = ft_strjoin(arr_env[i], lst_env->value);
		i++;
		lst_env = lst_env->next;
	}
	arr_env[i] = NULL;
	return (arr_env);
}
