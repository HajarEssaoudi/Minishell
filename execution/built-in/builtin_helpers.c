/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:26:30 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/30 21:08:01 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	malloc_failed_free(t_tok *tok, t_shell *shell, char **env)
{
	if (tok)
		free_tok(tok);
	if (shell)
		ft_clear(env, shell, tok);
	exit(2);
}

static int	valid_variable_name(char *str)
{
	int	i;

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

t_env	*create_env_node(char *str_env)
{
	t_env	*node_env;
	char	*equal;

	node_env = malloc(sizeof(t_env));
	if (!node_env)
		return (NULL);
	equal = ft_strchr(str_env, '=');
	if (equal)
	{
		node_env->key = ft_substr(str_env, 0, (equal - str_env));
		node_env->value = ft_strdup(equal + 1);
	}
	else
	{
		node_env->key = ft_strdup(str_env);
		node_env->value = ft_strdup(NULL);
	}
	node_env->next = NULL;
	return (node_env);
}

t_env	*add_to_env(char *str_env, t_shell *shell)
{
	t_env	*node_env;

	shell->exit_status = valid_variable_name(str_env);
	if (shell->exit_status == 1)
	{
		ft_printf(2, "minishell: export: %s: not a valid identifier\n",
			str_env);
		return (NULL);
	}
	node_env = create_env_node(str_env);
	if (!node_env)
	{
		ft_putstr_fd("allocation failed\n", 2);
		shell->exit_status = 2;
		return (NULL);
	}
	return (node_env);
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
