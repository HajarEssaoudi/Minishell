/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:47:12 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/03 07:47:39 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

extern int	g_flag;

int	open_file(char *path, t_shell *shell)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("open for read heredoc");
		shell->exit_status = EXIT_FAILURE;
	}
	return (fd);
}

char	*ft_expand(char *line, char **env)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp;
	char	*val;

	int(k), var_start, start;
	tmp1 = ft_strdup("");
	k = 0;
	while (line[k])
	{
		if (line[k] == '$' && (ft_isalpha(line[k + 1]) || line[k + 1] == '_'))
		{
			k++;
			var_start = k;
			while (line[k] && (ft_isalnum(line[k]) || line[k] == '_'))
				k++;
			tmp2 = ft_substr(line, var_start, k - var_start);
			val = ft_var(tmp2, env);
			tmp = ft_strjoin(tmp1, val);
			free(tmp1);
			free(tmp2);
			tmp1 = tmp;
		}
		else
		{
			start = k;
			while (line[k] && line[k] != '$')
			{
				if (line[k] == '$' && (!ft_isalpha(line[k + 1]) || line[k
						+ 1] != '_'))
				{
					k++;
				}
				else
					k++;
			}
			tmp2 = ft_substr(line, start, k - start);
			tmp = ft_strjoin(tmp1, tmp2);
			free(tmp1);
			free(tmp2);
			tmp1 = tmp;
		}
	}
	return (tmp1);
}

t_clean	*clean_heredoc(void)
{
	static t_clean	cleaner;

	return (&cleaner);
}

void	ft_herdoc(t_tok *tok, t_rederict *redir, char **env, t_shell *shell)
{
	char	*line;
	pid_t	pid;
	t_clean	*cleaner;

	int(fd), status, sig;
	g_flag = 1;
	pid = fork();
	cleaner = clean_heredoc();
	cleaner->env = env;
	cleaner->tok = tok;
	cleaner->shell = shell;
	if (pid == 0)
	{
		signal(SIGINT, ft_handl_herdoc);
		fd = open("./.tmp.txt", O_RDWR | O_CREAT | O_TRUNC, 0600);
		if (fd == -1)
		{
			perror("open heredoc");
			return ;
		}
		cleaner->fd = fd;
		while (1)
		{
			line = readline("> ");
			if (!line)
			{
				ft_printf(2,
					"Minishell: warning: here-document at line delimited by end-of-file (wanted `%s') \n");
				close(fd);
				free_tok(tok);
				ft_clear(env, shell, tok);
				exit(EXIT_SUCCESS);
			}
			if (ft_strcmp(line, redir->filename) == 0)
			{
				free_tok(tok);
				ft_clear(env, shell, tok);
				break ;
			}
			if (redir->flag && ft_strcmp(redir->flag, "2") == 0)
				line = ft_expand(line, env);
			ft_printf(fd, "%s\n", line);
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
