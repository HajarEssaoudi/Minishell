/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:47:12 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/16 08:45:44 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

extern int g_flag;

void	ft_out(t_tok *tok, char *filename, char **env, t_shell *shell)
{
	int	fd;

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
	if (tok->str && is_built_in(tok->str[0], env))
		execute_built_in(tok, shell, env);
	else if (tok->str || tok->execute)
		execute_with_execve(tok, shell, env);
	close(fd);
}

void	ft_in(t_tok *tok, char *filename, char **env, t_shell *shell)
{
	int	fd;

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

int	open_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("open for read heredoc");
		// ft_clear_exit
	}
	return (fd);
}

char	*ft_expand(char *line, t_tok *tok)
{
	int i = 0;
	char *str = ft_strdup("");
	char  tmp[2];
	while (line[i])
	{
		if (line[i] == '$' && (line[i + 1] == '_' || ft_isalpha(line[i + 1])))
		{
			str = ft_dollar(line, tok->env, str, &i, "0");
		}
		else{
			tmp[0] = line[i];
			tmp[1] = '\0';
			str = ft_strjoin(str, tmp);
			i++;
		}
	}
	free(line);
	return str;
}

void	ft_herdoc(t_tok *tok, char *delimiter, char **env, t_shell *shell)
{
	char	*line;
	int		fd;
	pid_t	pid;
	int		status;
	int		sig;

	g_flag = 1;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, ft_handl_herdoc);
		// g_flag = 0;
		fd = open("./.tmp.txt", O_RDWR | O_CREAT | O_TRUNC, 0600);
		if (fd == -1)
		{
			perror("open heredoc");
			return ;
		}
		while (1)
		{
			line = readline("> ");
			if (!line)
			{
				ft_putstr_fd("bash: warning: here-document at line ", 2);
				ft_putnbr_fd(shell->line, 2);
				ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
				ft_putstr_fd(delimiter, 2);
				ft_putstr_fd("')\n", 2);
				close(fd);
				exit(0);
			}
			if (ft_strcmp(line, delimiter) == 0)
				break ;
			line = ft_expand(line, tok);
			ft_putstr_fd(line, fd);
			ft_putstr_fd("\n", fd);
			free(line);
		}
		if (line)
			free(line);
		close(fd);
		exit(0);
	}
	else if (pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		signal(SIGINT, ft_handl);
		if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == SIGINT)
			{
				shell->exit_status = 130;
				unlink("./.tmp.txt");
				g_flag = 0;
				tok->heredoc_fd = -1;
				return ;
			}
		}
		else if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
	}
	fd = open_file("./.tmp.txt");
	tok->heredoc_fd = fd;
	unlink("./.tmp.txt");
	g_flag = 0;
}

void	ft_append(t_tok *tok, char *filename, char **env, t_shell *shell)
{
	int	fd;

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
