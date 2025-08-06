/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirectios_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 14:49:01 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/06 00:06:30 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	check_ambg(t_rederict *tmp, t_shell *shell)
{
	if (!ft_strcmp(tmp->flag, "1") || !tmp->filename)
	{
		ft_printf(2, "Minishell : ambiguous redirect\n");
		shell->exit_status = EXIT_FAILURE;
		return (0);
	}
	return (1);
}

int	out_red(t_redir *redir, char *filename, t_shell *shell)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		shell->exit_status = EXIT_FAILURE;
		return (0);
	}
	redir->last_out = filename;
	close(fd);
	return (1);
}

int	in_red(t_redir *redir, char *filename, t_shell *shell)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		shell->exit_status = EXIT_FAILURE;
		return (0);
	}
	redir->last_in = filename;
	close(fd);
	return (1);
}

void	ft_out(char *filename, t_shell *shell)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		shell->exit_status = EXIT_FAILURE;
		return ;
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		shell->exit_status = EXIT_FAILURE;
		return ;
	}
	close(fd);
}

void	ft_in( char *filename, t_shell *shell)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		shell->exit_status = EXIT_FAILURE;
		return ;
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		shell->exit_status = EXIT_FAILURE;
		return ;
	}
	close(fd);
}
