/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 00:45:20 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/05 11:01:10 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

extern int	g_flag;

static void	ft_heredoc_cleanup_and_exit(t_clean *cleaner, int fd, char *line)
{
	if (line)
		free(line);
	close(fd);
	free_tok(cleaner->tok);
	ft_clear(cleaner->env, cleaner->shell, cleaner->tok);
	exit(EXIT_SUCCESS);
}

static void	ft_heredoc_loop(int fd, t_rederict *redir, t_clean *cleaner)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_printf(2,
				"Minishell: warning: here-document delimited by EOF"
				"(wanted `%s')\n", redir->filename);
			ft_heredoc_cleanup_and_exit(cleaner, fd, NULL);
		}
		if (ft_strcmp(line, redir->filename) == 0)
			break ;
		if (redir->flag && ft_strcmp(redir->flag, "2") == 0)
		{
			expanded = ft_expand(line, cleaner->env);
			free(line);
			line = expanded;
		}
		ft_printf(fd, "%s\n", line);
		free(line);
	}
	free(line);
}
char *her_name(char ** env)
{
	char	*charact = "abcdefghijklmnopgrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	char *s = ".tmp.txt";
	char	*name;
	char	buffer[15];
	int		l = ft_strlen(charact);
	int		fd;
	int i;
	int j;
	
	name = malloc(24);
	if (!name)
		return (NULL);
	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
	{
		free(name);
		return (NULL);
	}
	if (read(fd, buffer, 15) != 15)
	{
		close(fd);
		free(name);
		return (NULL);
	}
	close(fd);
	i = 0;
	while(i < 15)
	{
		name[i] = charact[buffer[i] % l];
		i++;
	}
	j = 0;
	while (j < 8)
	{
		name[i++] = s[j];
		j++;
	}
	return (name);
}
static void	ft_heredoc_child(char *name, t_clean *cleaner, t_rederict *redir)
{
	int	fd;

	signal(SIGINT, ft_handle_herdoc);
	fd = open(name, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
	{
		perror("open heredoc");
		exit(EXIT_FAILURE);
	}
	cleaner->fd = fd;
	ft_heredoc_loop(fd, redir, cleaner);
	close(fd);
	free_tok(cleaner->tok);
	ft_clear(cleaner->env, cleaner->shell, cleaner->tok);
	exit(EXIT_SUCCESS);
}

static void	ft_heredoc_parent(char *name, pid_t pid, t_shell *shell, t_tok *tok)
{
	int	status;
	int	sig;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, ft_handle);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		shell->exit_status = 130;
		unlink(name);
		g_flag = 0;
		tok->heredoc_fd = -1;
	}
	else if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
}

void	ft_herdoc(t_tok *tok, t_rederict *redir, char **env, t_shell *shell)
{
	t_clean	*cleaner;
	pid_t	pid;
	char	*name;

	g_flag = 1;
	name = her_name(env);
	pid = fork();
	cleaner = clean_heredoc();
	cleaner->env = env;
	cleaner->tok = tok;
	cleaner->shell = shell;
	if (pid == 0)
		ft_heredoc_child(name, cleaner, redir);
	else if (pid > 0)
	{
		ft_heredoc_parent(name, pid, shell, tok);
	}
	tok->heredoc_fd = open_file(name, shell);
	unlink(name);
	g_flag = 0;
}
