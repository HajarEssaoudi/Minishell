/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:36:32 by hes-saou          #+#    #+#             */
/*   Updated: 2025/06/30 19:30:53 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	execute_redirect(t_tok *tok, char **env, t_shell *shell)
{
	t_rederict	*tmp;
	char		*delimiter = NULL;
	char		*last_out = NULL;
	char		*last_in = NULL;
	char		*last_append = NULL;
	pid_t		pid;
	int			status;

	tmp = tok->redirect;
	while (tmp)
	{
		if (ft_strcmp(tmp->type, ">") == 0)
			last_out = tmp->filename;
		else if (ft_strcmp(tmp->type, "<") == 0)
			last_in = tmp->filename;
		else if (ft_strcmp(tmp->type, ">>") == 0)
			last_append = tmp->filename;
		else if (ft_strcmp(tmp->type, "<<") == 0)
			delimiter = tmp->filename;
		tmp = tmp->next;
	}

	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		return;
	}
	if (pid == 0)
	{
		if (delimiter)
			ft_herdoc(tok, delimiter, env, shell);
		if (last_in)
			ft_in(tok, last_in, env, shell);
		if (last_out)
			ft_out(tok, last_out ,env, shell);
		if (last_append)
			ft_append(tok, last_append, env, shell);
		if (is_built_in(tok->str[0], env))
			execute_built_in(tok, shell, env);
		else
			execute_external_cmd(tok, env, 0);
		exit(0);
	}
	else
		waitpid(pid, &status, 0);
}

// void	execute_redirect(t_tok *tok)
// {
// 	t_rederict	*tmp = tok->redirect;
// 	int			fd;
// 	char		*last_in = NULL;
// 	char		*last_out = NULL;
// 	char		*out_type = NULL;
// 	t_rederict	*heredoc = NULL;


// 	while (tmp)
// 	{
// 		if (ft_strcmp(tmp->type, "<") == 0)
// 			last_in = tmp->filename;
// 		else if (ft_strcmp(tmp->type, ">") == 0 || ft_strcmp(tmp->type, ">>") == 0)
// 		{
// 			last_out = tmp->filename;
// 			out_type = tmp->type;
// 		}
// 		else if (ft_strcmp(tmp->type, "<<") == 0)
// 			heredoc = tmp;
// 		tmp = tmp->next;
// 	}
// 	if (last_in)
// 	{
// 		fd = open(last_in, O_RDONLY);
// 		if (fd < 0)
// 			perror("input <");
// 		else
// 			dup2(fd, STDIN_FILENO);
// 	}
// 	if (last_out)
// 	{
// 		if (ft_strcmp(out_type, ">") == 0)
// 			fd = open(last_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		else
// 			fd = open(last_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 		if (fd < 0)
// 			perror("output > or >>");
// 		else
// 			dup2(fd, STDOUT_FILENO);
// 	}
// }
