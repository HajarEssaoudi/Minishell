/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdelhaqmarouan <abdelhaqmarouan@student.42.fr>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-05 16:22:40 by abdelhaqmarouan   #+#    #+#             */
/*   Updated: 2025-08-05 16:22:40 by abdelhaqmarouan  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parsing/parsing.h"
# include "execution/execution.h"

void	print_str_array(char **arr);
void	print_tok(t_tok *tok);
t_shell	*initialise_struct(char **env, t_shell *shell, t_tok *tok);

#endif
