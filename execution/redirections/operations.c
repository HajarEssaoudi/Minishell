/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:47:12 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/27 23:45:27 by hes-saou         ###   ########.fr       */
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

void	ft_in(t_tok *tok, char *filename, char **env, t_shell *shell)
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

int	open_file(char *path, t_shell *shell)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("open for read heredoc");
		shell->exit_status = EXIT_FAILURE;
		// ft_clear_exit
	}
	return (fd);
}

char	*ft_expand(char *line, char **env)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp;
	int		k;

	tmp1 = ft_strdup("");
	k = 0;
	while (line[k])
			{
				if (line[k] == '$' && (ft_isalpha(line[k + 1]) || line[k + 1] == '_'))
				{
					k++;
					int var_start = k;
					while (line[k] && (ft_isalnum(line[k]) || line[k] == '_'))
						k++;
					tmp2 = ft_substr(line, var_start, k - var_start);
					char *val = ft_var(tmp2, env);
					tmp = ft_strjoin(tmp1, val);
					free(tmp1);
					tmp1 = tmp;
				}
				else
				{
					int start = k;
					while (line[k] && line[k] != '$')
					{
						if (line[k] == '$' && (!ft_isalpha(line[k + 1]) || line[k + 1] != '_'))
							k++;
						else
							k++;
					}
					tmp2 = ft_substr(line, start, k - start);
					tmp = ft_strjoin(tmp1, tmp2);
					free(tmp1); free(tmp2);
					tmp1 = tmp;
				}
			}
		return (tmp1);
}

void	ft_herdoc(t_tok *tok, t_rederict *redir, char **env, t_shell *shell)
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
				ft_putstr_fd("Minishell: warning: here-document at line ", 2);
				ft_putnbr_fd(shell->line, 2);
				ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
				ft_putstr_fd(redir->filename, 2);
				ft_putstr_fd("')\n", 2);
				close(fd);
				exit(EXIT_SUCCESS);
			}
			if (ft_strcmp(line, redir->filename) == 0)
				break ;
			// printf("quot => %d\n", tok->quot);
			if (redir->flag && ft_strcmp(redir->flag, "2") == 0)
				line = ft_expand(line, env);
			ft_putstr_fd(line, fd);
			ft_putstr_fd("\n", fd);
			free(line);
		}
		if (line)
			free(line);
		close(fd);
		exit(EXIT_SUCCESS);
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
	fd = open_file("./.tmp.txt", shell);
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
