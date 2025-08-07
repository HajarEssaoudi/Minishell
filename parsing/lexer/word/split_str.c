/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 11:00:20 by mabdelha          #+#    #+#             */
/*   Updated: 2025/08/07 11:00:22 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing.h"

void	add_split2(t_split *split, t_split *new_split)
{
	t_split	*tmp;

	tmp = split;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_split;
}

t_split	*split_node(char *str, int quoted, char *flag)
{
	t_split	*tmp;

	tmp = malloc(sizeof(t_split));
	if (!tmp)
		return (NULL);
	if (str)
		tmp->str = ft_strdup(str);
	else
		tmp->str = ft_strdup("");
	tmp->quoted = quoted;
	tmp->flag = flag;
	tmp->next = NULL;
	return (tmp);
}

void	add_split(t_split **split, char *str, int quoted, char *flag)
{
	t_split	*tmp;
	int		l;

	tmp = split_node(str, quoted, flag);
	if (!tmp)
		return ;
	tmp->first_space = 0;
	tmp->last_space = 0;
	l = 0;
	if (str)
	{
		l = ft_strlen(str);
		if ((str[0] == ' ' || str[0] == '\t') && !quoted)
			tmp->first_space = 1;
		if (l > 0 && (str[l - 1] == ' ' || str[l - 1] == '\t') && !quoted)
			tmp->last_space = 1;
	}
	if (!*split || !split)
		*split = tmp;
	else
		add_split2(*split, tmp);
}
