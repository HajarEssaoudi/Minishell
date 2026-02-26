/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdelhaqmarouan <abdelhaqmarouan@student.42.fr>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-09 09:51:46 by abdelhaqmarouan   #+#    #+#             */
/*   Updated: 2025-05-09 09:51:46 by abdelhaqmarouan  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_div *handle_redirect_output(char *input, int *i, t_div *div)
{
    if (!check_redirect1(input))
    {
        add_ch(&div, "output", ">");
        (*i)++;
    }
    else
        return (NULL);
    return (div);
}

t_div *handle_redirect_input(char *input, int *i, t_div *div)
{
    if (!check_redirect1(input))
    {
        add_ch(&div, "input", "<");
        (*i)++;
    }
    else
        return (NULL);
    return (div);
}

t_div *handle_redirect_append(char *input, int *i, t_div *div)
{
    if (!check_redirect2(input))
    {
        add_ch(&div, "append", ">>");
        (*i)++;
    }
    else
        return (NULL);
    return (div);
}

t_div *handle_redirect_heredoc(char *input, int *i, t_div *div)
{
    if (!check_redirect2(input))
    {
        add_ch(&div, "heredoc", "<<");
        (*i)++;
    }
    else
        return (NULL);
    return (div);
}

t_div *ft_operator(char *input, int *i, t_div *div)
{
    if (input[*i] == '|')
        div = handle_pip(input, i, div);
    else if (input[*i] == '>' && input[*i + 1] != '>')
        div = handle_redirect_output(input, i, div);
    else if (input[*i] == '<' && input[*i + 1] != '<')
        div = handle_redirect_input(input, i, div);
    else if (input[*i] == '>' && input[*i + 1] == '>')
        div = handle_redirect_append(input, i, div);
    else if (input[*i] == '<' && input[*i + 1] == '<')
        div = handle_redirect_heredoc(input, i, div);
    else if (!div)
    {
        // free_div(div);
        return (NULL);
    }
    return (div);
}
