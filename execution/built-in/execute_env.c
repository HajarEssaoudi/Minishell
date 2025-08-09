/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:13:40 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/09 02:58:11 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	execute_env(t_tok *tok, t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->env;
	if (tok->str[1])
	{
		write(2, "env: too many arguments\n", 25);
		return (EXIT_NOT_FOUND);
	}
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
