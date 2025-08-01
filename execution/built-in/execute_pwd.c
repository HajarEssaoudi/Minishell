/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:10:17 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/01 21:34:17 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	execute_pwd(t_shell *shell)
{
	t_env	*tmp;
	char	*path;

	tmp = shell->env;
	path = get_path();
	if (shell->pwd)
		return (printf("%s\n", shell->pwd), 0);
	else if (path)
	{
		printf("%s\n", get_path());
		return (0);
	}
	else
	{
		while (tmp)
		{
			if (ft_strcmp(tmp->key, "PWD") == 0)
			{
				printf("%s\n", tmp->value);
				return (0);
			}
			tmp = tmp->next;
		}
	}
	return (1);
}
