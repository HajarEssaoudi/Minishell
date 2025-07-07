/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:47:12 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/07 16:23:26 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	ft_out(t_tok *tok,char *filename, char **env, t_shell *shell)
{
	int		fd;
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	ft_in(t_tok *tok,char *filename, char **env, t_shell *shell)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

// void	ft_herdoc(t_tok *tok, char *delimiter, char **env, t_shell *shell)
// {
// 	char	*line;
// 	int		pipefd[2];

// 	if (pipe(pipefd) == -1)
// 	{
// 		perror("pipe");
// 		return;
// 	}
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line || ft_strcmp(line, delimiter) == 0)
// 			break;
// 		write(pipefd[1], line, ft_strlen(line));
// 		write(pipefd[1], "\n", 1);
// 		free(line);
// 	}
// 	free(line);
// 	close(pipefd[1]);
// 	tok->heredoc_fd = pipefd[0];
// 	// dup2(pipefd[0], STDIN_FILENO);
// 	// close(pipefd[0]);
// }


void	ft_herdoc(t_tok *tok, char *delimiter, char **env, t_shell *shell)
{
	char	*line;
	int		fd;
	char	tmp_path[] = "./.tmp.txt";

	fd = open(tmp_path , O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
	{
		perror("open heredoc");
		return;
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
	fd = open(tmp_path, O_RDONLY);
	if (fd == -1)
	{
		perror("open for read heredoc");
		return;
	}
	tok->heredoc_fd = fd;
	unlink(tmp_path);
}


void	ft_append(t_tok *tok, char *filename,char **env, t_shell *shell)
{
	int		fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}
