/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:03:52 by mabdelha          #+#    #+#             */
/*   Updated: 2025/06/12 18:49:19 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_add_type(t_lexer *lexer, char *type, int *st, int new_st)
{
	if (lexer->type)
		free(lexer->type);
	lexer->type = ft_strdup(type);
	*st = new_st;
}

void	ft_get_type(t_lexer *lexer, int *st)
{
	if (!(ft_strncmp(lexer->args, "./", ft_strlen("./"))) && (!*st || *st == 3))
		ft_add_type(lexer, "execute", st, 5);
	else if (!(ft_strncmp(lexer->type, "string", ft_strlen("string"))) && (!*st
			|| *st == 3))
		ft_add_type(lexer, "cmd", st, 1);
	else if ((*st == 1 || *st == 2) && !(ft_strncmp(lexer->type, "string",
				ft_strlen("string"))))
		ft_add_type(lexer, "string", st, 2);
	else if (*st == 4 && !(ft_strncmp(lexer->type, "string",
				ft_strlen("string"))))
		ft_add_type(lexer, "filename", st, 3);
	else if (!(ft_strncmp(lexer->type, "output", ft_strlen("output")))
		|| !(ft_strncmp(lexer->type, "input", ft_strlen("input")))
		|| !(ft_strncmp(lexer->type, "append", ft_strlen("append")))
		|| !(ft_strncmp(lexer->type, "heredoc", ft_strlen("heredoc"))))
		*st = 4;
	else if (!(ft_strncmp(lexer->type, "pip", ft_strlen("pip"))))
		*st = 0;
}

void	ft_type(t_lexer *lexer)
{
	int	st;

	st = 0;
	while (lexer)
	{
		ft_get_type(lexer, &st);
		lexer = lexer->next;
	}
}
