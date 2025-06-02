/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:19:31 by hes-saou          #+#    #+#             */
/*   Updated: 2025/06/02 11:46:43 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *init_lst_env(t_env *env, char **arr_env)
{
	int	i;

	i = 0;
	while(arr_env[i])
	{
		env->key = NULL;
		env->value = ft_strrchr(arr_env[i], '=') + 1;
		i++;
	}
	return (env);
}

void print_list(t_env *env)
{
	int i;
	t_env *tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		printf("value == %s\n", tmp->value);
		tmp = tmp->next;
	}
}

t_env *create_list_env(char **arr_env)
{
	t_env *lst_env;

	lst_env = malloc(sizeof(t_env));
	if (!lst_env)
	{
		//ft_clear_exit
		ft_putstr_fd("allocation failed\n", 2);
	}
	lst_env->key = NULL;
	lst_env->value = NULL;
	lst_env = init_lst_env(lst_env, arr_env);
	print_list(lst_env);
	return(lst_env);
}
