/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 01:33:48 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/05 01:34:04 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char	*ft_expand(char *line, char **env)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp;
	char	*val;

	int (k), var_start, start;
	tmp1 = ft_strdup("");
	k = 0;
	while (line[k])
	{
		if (line[k] == '$' && (ft_isalpha(line[k + 1]) || line[k + 1] == '_'))
		{
			k++;
			var_start = k;
			while (line[k] && (ft_isalnum(line[k]) || line[k] == '_'))
				k++;
			tmp2 = ft_substr(line, var_start, k - var_start);
			val = ft_var(tmp2, env);
			tmp = ft_strjoin(tmp1, val);
			free(tmp1);
			free(tmp2);
			tmp1 = tmp;
		}
		else
		{
			start = k;
			while (line[k] && line[k] != '$')
			{
				if (line[k] == '$' && (!ft_isalpha(line[k + 1]) || line[k
							+ 1] != '_'))
				{
					k++;
				}
				else
					k++;
			}
			tmp2 = ft_substr(line, start, k - start);
			tmp = ft_strjoin(tmp1, tmp2);
			free(tmp1);
			free(tmp2);
			tmp1 = tmp;
		}
	}
	return (tmp1);
}
