/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 22:59:42 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/06 22:59:44 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "execution/execution.h"
# include "parsing/parsing.h"

void	print_str_array(char **arr);
void	print_tok(t_tok *tok);
t_shell	*initialise_struct(char **env, t_shell *shell, t_tok *tok);

#endif
