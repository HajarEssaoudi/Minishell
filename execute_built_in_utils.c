/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:49:53 by hes-saou          #+#    #+#             */
/*   Updated: 2025/06/04 16:38:14 by hes-saou         ###   ########.fr       */
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

void	list_env_variables(t_shell *shell)
{
	printf("wa mazaaal waaa lbssala hadi zid les variables w hnina\n");
}
