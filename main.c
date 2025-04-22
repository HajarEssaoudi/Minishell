/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:11:00 by hes-saou          #+#    #+#             */
/*   Updated: 2025/04/22 22:27:51 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear(t_utils *utils)
{
	if (utils->input)
		free(utils->input);
	if (utils)
		free(utils);
	exit(0);
}



int	execute_simple_command(t_utils *utils)
{
	char	*path1;
	char	*path2;
	char	**cmd;
	char	*cmdOption;
	char	*argv[3];
	char	*envp[] = {NULL};

	cmd = ft_split(utils->input, ' ');
	if (!cmd || !cmd[0])
		return (1);
	path1 = ft_strjoin("/bin/", cmd[0]);
	path2 = ft_strjoin("/usr/bin/", cmd[0]);
	if (access(path1, X_OK) == 0)
		utils->cmdPath = path1;
	else if (access(path2, X_OK) == 0)
		utils->cmdPath = path2;
	if (!utils->cmdPath)
		return (1);
	cmdOption = ft_strchr(utils->input, '-');
	utils->option = cmdOption;
	// printf("Helooooooo = %s\n", utils->cmdPath);
	argv[0] = utils->cmdPath;
	argv[1] = utils->option;
	argv[2] = NULL;

	execve(utils->cmdPath, argv, envp);
	perror("execve failed");
	free(path1);
	free(path2);
	ft_clear(utils);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_utils	*utils;
	pid_t	pid;
	int status;

	utils = malloc(sizeof(t_utils));
	while (1)
	{
		utils->input = readline("Minishell$> ");
		if (!utils->input)
			return (1);
		add_history(utils->input);
		pid = fork();
		if (pid == 0)
		{
			if (execute_simple_command(utils) == -1)
			{
				perror("minishell failed");
				exit(EXIT_FAILURE);
			}
		}
		else if (pid > 0)
		{
			waitpid(pid, &status, 0);
		}
		else
		{
			perror("fork failed");
			return (1);
		}
	}
	ft_clear(utils);
}
