/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:15:57 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/02 14:26:17 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	malloc_failed_free(t_tok *tok, t_shell *shell, char **env)
{
	if (tok)
		free_tok(tok);
	if (shell)
		ft_clear(env, shell, tok);
	exit(2);
}

t_env	*init_node_env(char *str_env, t_shell *shell)
{
	t_env	*node_env;
	char	*equal;

	node_env = malloc(sizeof(t_env));
	if (!node_env)
	{
		ft_putstr_fd("allocation failed\n", 2);
		shell->exit_status = EXIT_FAILURE;
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
		node_env->key = ft_substr(str_env, 0, (equal - str_env));
		node_env->value = ft_strdup(NULL);
		node_env->next = NULL;
	}
	return (node_env);
}

t_env	*create_list_env(char **arr_env, t_tok *tok, t_shell *shell)
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
		new_node = init_node_env(arr_env[i], shell);
		if (new_node == NULL)
		{
			ft_putstr_fd("allocation failed\n", 2);
			malloc_failed_free(tok, shell, arr_env);
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
