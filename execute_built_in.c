/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:05:30 by hes-saou          #+#    #+#             */
/*   Updated: 2025/06/01 00:01:10 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

char	*get_path()
{
	char	*buffer;
	char	*cwd;
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
	cwd = ft_strdup(buffer);
	free(buffer);
	return (cwd);
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

void	execute_cd(t_tok *tok, t_shell *shell)
{
	char	*home_path;

	shell->old_path = get_path();
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
		if (chdir(tok->str[1]) == -1)
		{
			perror("cd");
		}
	}
	// change_env_paths(tok);
}

void	execute_pwd(t_tok *tok, t_shell *shell)
{
	printf("the old path => %s\n", shell->old_path);
	shell->current_path = get_path();
	printf("the new path => %s\n", shell->current_path);
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

void	execute_echo(t_tok *tok)
{
	int	i;

	i = 1;
	while (tok->str[i])
		i++;
	if (i > 1)
	{
		if (ft_strncmp(tok->str[1], "-n", ft_strlen(tok->str[1])) == 0)
		{
			print_strings(tok->str, 2);
		}
		else
		{
			print_strings(tok->str, 1);
			printf("\n");
		}
	}
	else
		printf("\n");
}

void	execute_env(t_tok *tok)
{
	int	i;

	i = 0;
	while (tok->env)
	{
		printf("%s\n", tok->env[i]);
		i++;
	}
}

void	execute_exit(t_tok *tok)
{
	// ft_cleaar
	printf("exit\n");
	exit(0);
}