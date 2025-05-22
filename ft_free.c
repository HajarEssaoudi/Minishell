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

