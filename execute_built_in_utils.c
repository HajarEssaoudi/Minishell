/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:49:53 by hes-saou          #+#    #+#             */
/*   Updated: 2025/06/12 16:46:58 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		// perror("getcwd");
		return (NULL);
	}
	return (cwd);
}

void	change_env_paths(t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "OLDPWD") == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(shell->old_path);
			break ;
		}
		tmp = tmp->next;
	}
	tmp = shell->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(shell->current_path);
			break ;
		}
		tmp = tmp->next;
	}
}

void	print_strings(char **str, int i)
{
	while (str[i])
	{
		printf("%s", str[i]);
		i++;
		if (str[i])
			printf(" ");
	}
}

// t_env	*sort_var(t_shell *shell)
// {
// 	t_env	*env;
// 	t_env	*head;
// 	t_env	*tmp;

// 	env = shell->env;
// 	head = env;
// 	tmp = env;
// 	while (env->next)
// 	{
// 		if (ft_strcmp(env->key, env->next->key) > 0)
// 		{
// 			tmp->key = env->key;
// 			tmp->value = env->value;
// 			env->key = env->next->key;
// 			env->value = env->next->value;
// 			env->next->key = tmp->key;
// 			env->next->value = tmp->value;
// 			env = head;
// 		}
// 		env = env->next;
// 	}
// 	return (env);
// }

t_env	*sort_var(t_shell *shell)
{
	t_env	*env;
	t_env	*head;
	char	*tmp_key;
	char	*tmp_value;
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
				tmp_key = env->key;
				tmp_value = env->value;
				env->key = env->next->key;
				env->value = env->next->value;
				env->next->key = tmp_key;
				env->next->value = tmp_value;
				sorted = 0;
			}
			env = env->next;
		}
	}
	return (head);
}


void print_env(t_env *env)
{
	int i;
	t_env *tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

void	list_env_variables(t_shell *shell)
{
	t_env	*env;

	env = sort_var(shell);
	print_env(env);
}
