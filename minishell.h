/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 22:59:42 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/07 09:46:08 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "execution/execution.h"
# include "parsing/parsing.h"

t_shell	*initialise_struct(char **env, t_shell *shell, t_tok *tok);

#endif
