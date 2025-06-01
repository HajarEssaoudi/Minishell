/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:05:30 by hes-saou          #+#    #+#             */
/*   Updated: 2025/06/01 18:30:40 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path()
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
	if (shell->old_path == NULL)
	{
		// change pwd and oldpwd
	}
	//to be checked later
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
	shell->current_path = get_path();
	if (shell->current_path == NULL)
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
	}
	// change_env_paths(shell);
}

void	execute_pwd(t_tok *tok, t_shell *shell)
{
	shell->current_path = get_path();
	printf("%s\n", shell->current_path);
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

	if (tok->str[1])
	{
		if (tok->str[2] && ft_strncmp(tok->str[1], "-n", ft_strlen(tok->str[1])) == 0)
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

void	execute_env(t_tok *tok, t_shell *shell)
{
	int	i;

	i = 0;
	// printf("%s\n", shell->old_path);
	while (tok->env)
	{
		printf("%s\n", tok->env[i]);
		i++;
	}
}

void	execute_exit(t_tok *tok)
{
	unsigned int exit_status;

	if (!tok->str[1])
	{
		// ft_clear
		printf("exit\n");
		exit(0);
	}
	else
	{
		if (!ft_strdigit(tok->str[1]))
		{
			// ft_clear
			printf("exit\n");
			exit(2);
		}
		else
		{
			if (!tok->str[2])
			{
				exit_status = (unsigned int)ft_atoi(tok->str[1]);
				// ft_clear
				printf("exit\n");
				exit(exit_status);
			}
			else
			{
				printf("exit\n");
				ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
			}
		}
	}
}