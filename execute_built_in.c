/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:05:30 by hes-saou          #+#    #+#             */
/*   Updated: 2025/05/01 19:08:15 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(t_tok *tok)
{
	char *buffer;
	size_t size = PATH_MAX;

	buffer = malloc(size);
	if (!buffer)
		exit(1);
	if (getcwd(buffer, size) == NULL)
	{
		perror("getcwd");
		free(buffer);
		return (NULL);
	}
	tok->pwd = buffer;
	return (buffer);
}

void	execute_cd(t_tok *tok)
{
	if (tok->str[1] == NULL || ft_strncmp(tok->str[1], "~", ft_strlen(tok->str[1])) == 0)
	{
		if (chdir("/home/hes-saou") != 0)
		{
			perror("cd");
		}
	}
	else if (chdir(tok->str[1]) != 0)
	{
		perror("cd");
	}
}

void	execute_pwd(t_tok *tok)
{
	printf("the old path => %s\n", tok->old_pwd);
	if (get_path(tok))
	{
		printf("the new path => %s\n", tok->pwd);
	}
}

void	execute_echo(t_tok *tok)
{
	ft_putstr_fd(tok->str[1], 1);
}

void	execute_env(t_tok *tok)
{
	int	i;

	i = 0;
	while(tok->env)
	{
		ft_putstr_fd(tok->env[i], 1);
		printf("\n");
		i++;
	}
}