/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:26:30 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/01 00:09:27 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static int	valid_variable_name(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (i == 0 && !ft_isalpha(str[i]) && str[i] != '_')
			return (1);
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	if (i == 0 && str[i] == '=')
		return (1);
	return (0);
}

t_env	*init_node_env(char *str_env,t_shell *shell, int f)
{
	t_env	*node_env;
	char	*equal;

	node_env = malloc(sizeof(t_env));
	if (!node_env)
	{
		ft_putstr_fd("allocation failed1\n", 2);
		shell->exit_status = EXIT_FAILURE;
		// clear_exit;
	}
	if (f == EXPORT)
	{
		shell->exit_status = valid_variable_name(str_env);
		if (shell->exit_status == 1)
		{
			ft_printf(2, "minishell: export: %s: not a valid identifier\n", str_env);
			return (NULL);
		}
	}
	equal = ft_strchr(str_env, '=');
	if (equal)
	{
		node_env->key = ft_substr(str_env, 0, (equal - str_env));
		node_env->value = ft_strdup(equal + 1);
		node_env->next = NULL;
	}
	else
	{

		node_env->key = ft_strdup(str_env);
		node_env->value = NULL;
		node_env->next = NULL;
	}
	return (node_env);
}

t_env	*create_list_env(char **arr_env, t_shell *shell)
{
	t_env	*head;
	t_env	*tmp;
	int		i;
	t_env	*new_node;

	i = 0;
	head = NULL;
	tmp = NULL;
	while (arr_env[i])
	{
		new_node = init_node_env(arr_env[i],shell, CREATE_LIST);
		if (new_node == NULL)
		{
			ft_putstr_fd("allocation failed2\n", 2);
			// clear_exit
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
	count = 0;
	tmp = lst;
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
	if (!arr_env)
	{
		ft_putstr_fd("allocation failed3\n", 2);
		// ft_clear and exit
	}
	while (lst_env)
	{
		arr_env[i] = ft_strjoin_env(lst_env->key, lst_env->value, '=');
		if (!arr_env[i])
		{
			ft_putstr_fd("allocation failed4\n", 2);
			// ft_clear and exit
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

void	print_env(t_env *env)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		if (tmp->value)
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		else if (!tmp->value)
			printf("declare -x %s\n", tmp->key);
		tmp = tmp->next;
	}
}
