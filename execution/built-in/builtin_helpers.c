/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:26:30 by hes-saou          #+#    #+#             */
/*   Updated: 2025/06/13 12:25:44 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

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

	if (!lst)
		return (-1);
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
	free_str(arr_env, 0);
	arr_env = malloc(sizeof(char *) * (ft_lst_size(lst_env) + 1));
	if (!arr_env)
	{
		ft_putstr_fd("allocation failed\n", 2);
		//ft_clear and exit
	}
	while (lst_env)
	{
		arr_env[i] = ft_strjoin_env(lst_env->key, lst_env->value, '=');
		if (!arr_env[i])
		{
			ft_putstr_fd("allocation failed\n", 2);
			//ft_clear and exit
		}
		i++;
		lst_env = lst_env->next;
	}
	arr_env[i] = NULL;
	return (arr_env);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!(*lst))
		*lst = new;
	else
	{
		last = *lst;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}
