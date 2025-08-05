/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:10:17 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/05 02:35:52 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	check_path(t_shell *shell)
{
	if (shell->current_path)
	{
		printf("%s\n", shell->current_path);
		return (0);
	}
	return (1);
}

int	execute_pwd(t_shell *shell)
{
	t_env	*tmp;
	char	*path;

	tmp = shell->env;
	path = get_path();
	if (!check_path(shell))
		return (0);
	if (path)
	{
		printf("%s\n", path);
		free(path);
		return (0);
	}
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			printf("%s\n", tmp->value);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
