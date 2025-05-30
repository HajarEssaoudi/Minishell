/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdelhaqmarouan <abdelhaqmarouan@student.42.fr>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-09 10:04:12 by abdelhaqmarouan   #+#    #+#             */
/*   Updated: 2025-05-09 10:04:12 by abdelhaqmarouan  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_div(t_div *div)
{
    t_div   *tmp;
    while (div)
    {
        tmp = div->next;
        if (div->args)
            free(div->args);
        if (div->type)
            free(div->type);
        free(div);
        div = tmp;
    }
}

void    free_tok(t_tok *tok)
{
    t_tok *cur;
    while (tok)
    {
        cur = tok->next;
        if (tok->append)
            free(tok->append);
        if (tok->env)
        {
            int i = 0;
            while (tok->env[i])
            {
                free(tok->env[i]);
                i++;
            }
            free(tok->env);
        }
        if (tok->str)
        {
            int i = 0;
            while (tok->str[i])
            {
                free(tok->str[i]);
                i++;
            }
            free(tok->str);
        }
        if (tok->execute)
            free(tok->execute);
        // if (tok->filename)
        //     free(tok->filename);
        if (tok->heredoc)
            free(tok->heredoc);
        if (tok->input)
            free(tok->input);
        if (tok->old_pwd)
            free(tok->old_pwd);
        if (tok->output)
            free(tok->output);
        if (tok->path)
            free(tok->path);
        if (tok->pip)
            free(tok->pip);
        if (tok->pwd)
            free(tok->pwd);
        tok = cur;
    }
}

void	free_str(char **str)
{
	int i = 0;
    while (str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}