/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-31 19:06:34 by mabdelha          #+#    #+#             */
/*   Updated: 2025-05-31 19:06:34 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_space_tab_newline(char *str, int i)
{
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	return (i);
}

void	add_ch(t_lexer **lexer, char *type, char *input)
{
	t_lexer	*token;
	t_lexer	*tmp;

	token = malloc(sizeof(t_lexer));
	token->args = ft_strdup(input);
	token->type = ft_strdup(type);
	token->next = NULL;
	if (!*lexer)
	{
		*lexer = token;
	}
	else
	{
		tmp = *lexer;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = token;
	}
}

char	*ft_special_caract(char *result, char *var)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strjoin(result, var);
	free(var);
	free(result);
	return (tmp);
}

char	**ft_argv(char **argv, char *arg)
{
	int		j;
	char	**argv2;
	int		i;

	j = 0;
	while (argv && argv[j])
		j++;
	argv2 = malloc(sizeof(char *) * (j + 2));
	i = 0;
	while (argv && argv[i])
	{
		argv2[i] = ft_strdup(argv[i]);
		i++;
	}
	argv2[i] = ft_strdup(arg);
	argv2[i + 1] = NULL;
	if (argv)
		free(argv);
	return (argv2);
}
