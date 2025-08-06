/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:57:50 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/06 00:47:43 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/execution.h"
#include "parsing.h"

int		g_flag = 0;

void	print_str_array(char **arr)
{
	int	i;

	if (!arr)
	{
		printf("(null)\n");
		return ;
	}
	i = 0;
	while (arr[i])
	{
		printf("  [%d]: %s\n", i, arr[i]);
		i++;
	}
}

void	print_tok(t_tok *tok)
{
	int	index;
	int	j;

	index = 0;
	while (tok)
	{
		printf("Token #%d:\n", index);
		printf(" path: %s\n", tok->path ? tok->path : "(null)");
		print_str_array(tok->str);
		printf("herdoc_fd == %d\n", tok->heredoc_fd);
		printf("quot => %d\n", tok->quot);
		j = 0;
		while (tok->redirect)
		{
			printf("redirect #%d\n", j);
			printf("%s %s %s\n", tok->redirect->type, tok->redirect->filename,
				tok->redirect->flag);
			tok->redirect = tok->redirect->next;
			j++;
		}
		printf(" pip: %s\n", tok->pip ? tok->pip : "(null)");
		printf("------------------------\n");
		tok = tok->next;
		index++;
	}
}
t_shell	*initialise_struct(char **env, t_shell *shell, t_tok *tok)
{
	shell = malloc(sizeof(t_shell));
	if (!shell)
	{
		ft_clear(env, shell);
	}
	shell->env = create_list_env(env, tok, shell);
	shell->exit_status = 0;
	shell->saved_stdout = 0;
	shell->saved_stdin = 0;
	shell->current_path = NULL;
	shell->old_path = NULL;
	shell->pwd = get_path();
	return (shell);
}

// int	main(int argc, char **argv, char **env)
// {
// 	char	*prompt;
// 	char	**cp_env;
// 	t_tok	*tok;
// 	t_shell	*shell;
// 	int		status;
// 	int		is_pipeline;
// 	t_tok	*tmp;

// 	(void)argc;
// 	(void)argv;
// 	signal(SIGINT, ft_handle);
// 	signal(SIGQUIT, SIG_IGN);
// 	cp_env = copy_env(env);
// 	tok = NULL;
// 	shell = NULL;
// 	shell = initialise_struct(env, shell, tok);
// 	if (!shell)
// 		return (1);
// 	while (1)
// 	{
// 		prompt = readline("Minishell$> ");
// 		if (!prompt)
// 		{
// 			status = shell->exit_status;
// 			ft_clear(cp_env, shell, tok);
// 			ft_printf(2, "exit\n");
// 			exit(status);
// 		}
// 		if (!prompt[0])
// 			continue ;
// 		tok = get_tok(prompt, cp_env, shell->exit_status);
// 		if (!tok)
// 			shell->exit_status = 2;
// 		if (tok != NULL)
// 		{
// 			tok->heredoc_fd = -1;
// 			is_pipeline = 0;
// 			tmp = tok;
// 			while (tmp)
// 			{
// 				if (tmp->pip && tmp->pip[0] == '|')
// 				{
// 					is_pipeline = 1;
// 					break ;
// 				}
// 				tmp = tmp->next;
// 			}
// 			execute_cmd(tok, shell, cp_env);
// 			cp_env = update_env_arr(shell->env, cp_env);
// 			if (!is_pipeline)
// 				free_tok(tok);
// 		}
// 		add_history(prompt);
// 		free(prompt);
// 	}
// 	// ft_clear(cp_env, shell, 0);
// 	return (0);
// }

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == 0)
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	len1 = ft_strlen_gnl(s1);
	size_t	len2 = ft_strlen_gnl(s2);
	char	*new_str = malloc(len1 + len2 + 1);
	size_t	i = 0, j = 0;

	if (!new_str)
		return (NULL);
	while (s1 && s1[i])
	{
		new_str[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
		new_str[i++] = s2[j++];
	new_str[i] = '\0';
	free(s1);
	return (new_str);
}

char	*ft_substr_gnl(char *s, unsigned int start, size_t len)
{
	size_t	i = 0;
	char	*sub;

	if (!s || start >= ft_strlen_gnl(s))
		return (ft_strjoin_gnl(NULL, ""));
	if (len > ft_strlen_gnl(s + start))
		len = ft_strlen_gnl(s + start);
	sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

static char	*read_until_newline(int fd, char *stash)
{
	char	*buffer;
	ssize_t	bytes;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes = 1;
	while (!ft_strchr_gnl(stash, '\n') && bytes != 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		buffer[bytes] = '\0';
		stash = ft_strjoin_gnl(stash, buffer);
	}
	free(buffer);
	return (stash);
}

static char	*extract_line(char *stash)
{
	size_t	len = 0;
	char	*line;

	if (!stash || stash[0] == '\0')
		return (NULL);
	while (stash[len] && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
	line = ft_substr_gnl(stash, 0, len);
	return (line);
}

static char	*save_remaining(char *stash)
{
	size_t	start = 0;
	char	*rest;

	while (stash[start] && stash[start] != '\n')
		start++;
	if (!stash[start])
	{
		free(stash);
		return (NULL);
	}
	rest = ft_substr_gnl(stash, start + 1, ft_strlen_gnl(stash) - start - 1);
	free(stash);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_until_newline(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	stash = save_remaining(stash);
	return (line);
}

int	main(int argc, char **argv, char **env)
{
	char	*prompt;
	char	**cp_env;
	t_tok	*tok;
	t_shell	*shell;
	int		status;
	int		is_pipeline;
	t_tok	*tmp;
	int		interactive;

	(void)argc;
	(void)argv;

	// Signal handling
	signal(SIGINT, ft_handle);
	signal(SIGQUIT, SIG_IGN);

	// Init env + shell
	cp_env = copy_env(env);
	tok = NULL;
	shell = NULL;
	shell = initialise_struct(env, shell, tok);
	if (!shell)
		return (1);

	interactive = isatty(fileno(stdin)); // check if interactive (tty)

	while (1)
	{
		if (interactive)
			prompt = readline("Minishell$> ");
		else
		{
			char *line = get_next_line(fileno(stdin));
			if (!line)
				break; // EOF
			prompt = ft_strtrim(line, "\n");
			free(line);
		}

		if (!prompt)
		{
			status = shell->exit_status;
			ft_clear(cp_env, shell);
			if (interactive) // only print "exit" in interactive mode
				ft_printf(2, "exit\n");
			exit(status);
		}

		if (!prompt[0])
		{
			free(prompt);
			continue;
		}

		tok = get_tok(prompt, cp_env, shell->exit_status);
		if (!tok)
			shell->exit_status = 2;

		if (tok != NULL)
		{
			tok->heredoc_fd = -1;
			is_pipeline = 0;
			tmp = tok;
			while (tmp)
			{
				if (tmp->pip && tmp->pip[0] == '|')
				{
					is_pipeline = 1;
					break;
				}
				tmp = tmp->next;
			}
			execute_cmd(tok, shell, cp_env);
			cp_env = update_env_arr(shell->env, cp_env);
			if (!is_pipeline)
				free_tok(tok);
		}

		if (interactive)
			add_history(prompt);

		free(prompt);
	}

	// Cleanup on non-interactive exit
	ft_clear(cp_env, shell);
	return (0);
}
