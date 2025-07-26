/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:19:13 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/26 01:29:50 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	free_list_env (t_env *env)
{
	t_env *tmp;
	while(env)
	{
		tmp = env->next;
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		free(env);
		env = tmp;
	}
}

void	ft_clear(char **cp_env,t_shell *shell,t_tok *tok)
{
	if (cp_env)
		free_str(cp_env);
	if (shell)
	{
		if (shell->env)
			free_list_env(shell->env);
		if (shell->pwd)
		{
			printf("OUPS\n");
			free(shell->pwd);
		}
		// if (shell->current_path)
		// 	free(shell->current_path);
		// if (shell->old_path)
		// 	free(shell->old_path);
		free(shell);
	}
}
