/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 22:59:42 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/07 10:05:56 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "execution/execution.h"
# include "parsing/parsing.h"

t_shell	*initialise_struct(char **env, t_shell *shell);

#endif
