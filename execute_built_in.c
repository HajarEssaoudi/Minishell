/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:05:30 by hes-saou          #+#    #+#             */
/*   Updated: 2025/04/30 14:43:43 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cd(t_tok *tok)
{
	if (chdir(tok->str[1]) != 0)
	{
		perror("cd");
	}
}

int	execute_pwd(t_tok *tok)
{
	char *buffer;
	size_t size = PATH_MAX;

	buffer = malloc(size);
	if (!buffer)
		return (1);
	if (getcwd(buffer, size) != NULL)
		printf("%s\n", buffer);
	else
		perror("getcwd");
	free(buffer);
	return (0);
}