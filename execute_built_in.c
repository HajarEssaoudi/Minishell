/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:05:30 by hes-saou          #+#    #+#             */
/*   Updated: 2025/05/02 19:00:09 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char 	*get_path(t_tok *tok)
{
	char	*buffer;
	size_t	size;

	size = PATH_MAX;
	buffer = malloc(size);
	if (!buffer)
		exit(1);
	if (getcwd(buffer, size) == NULL)
	{
		perror("getcwd");
		free(buffer);
		return (NULL);
	}
	tok->pwd = ft_strdup(buffer);
	free(buffer);
	return (tok->pwd);
}

char	*get_home_path(t_tok *tok)
{
	char	*home;
	int		i;
	int		j;

	i = 0;
	home = NULL;
	while (tok->env[i])
	{
		if (ft_strncmp(tok->env[i], "HOME=", 5) == 0)
		{
			home = ft_strdup(&(tok->env[i][5]));
			if (!home)
			{
				perror("malloc");
				return (NULL);
			}
			return (home);
		}
		i++;
	}
	return (NULL);
}

void	execute_cd(t_tok *tok)
{
	char	*home_path;

	tok->old_pwd = get_path(tok);
	if (tok->str[1] == NULL || ft_strncmp(tok->str[1], "~",
			ft_strlen(tok->str[1])) == 0)
	{
		home_path = get_home_path(tok);
		if (!home_path)
			ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
		if (chdir(home_path) != 0)
			perror("cd");
	}
	else
	{
		if (access(tok->str[1], F_OK) == 0)
		{
			if (chdir(tok->str[1]) != 0)
				perror("cd");
		}
	}
	// change_env_paths(tok);
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
	int i;

	i = 0;
	while (tok->env)
	{
		printf("%s\n", tok->env[i]);
		i++;
	}
}