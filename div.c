/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   div.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-23 02:22:57 by mabdelha          #+#    #+#             */
/*   Updated: 2025/05/05 02:22:30 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_ch(t_div **div, char *type, char *input)
{
	t_div	*token;
	t_div	*tmp;

	token = malloc(sizeof(t_div));
	token->args = ft_strdup(input);
	token->type = ft_strdup(type);
	token->next = NULL;
	if (!*div)
		*div = token;
	else
	{
		tmp = *div;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = token;
	}
}

t_div	*ft_operator(char *input, int *i, t_div *div)
{
	if (input[*i] == '|' && !(check_pip(input)))
		add_ch(&div, "pip", "|"), (*i)++;
	else if (input[*i] == '>' && input[*i + 1] != '>'
		&& !(check_redirect(input)))
		add_ch(&div, "output", ">"), (*i)++;
	else if (input[*i] == '<' && input[*i + 1] != '<'
		&& !(check_redirect(input)))
		add_ch(&div, "input", "<"), (*i)++;
	else if (input[*i] == '>' && input[*i + 1] == '>'
		&& !(check_redirect2(input)))
	{
		(*i)++;
		add_ch(&div, "append", ">>");
		(*i)++;
	}
	else if (input[*i] == '<' && input[*i + 1] == '<'
		&& !(check_redirect2(input)))
	{
		(*i)++;
		add_ch(&div, "heredoc", "<<");
		(*i)++;
	}
	else
		return (NULL);
	return (div);
}

t_div	*ft_str(char *input, int *i, t_div *div, char **cp_env)
{
	char	*str;
	int		j;

	str = NULL;
	//hi labas ftrti mohim hna kantchikiw bin "" et '' et li ma dakhlche fihom y3ni matalan hello et "hello" fhemti
	if (input[*i] == '"' || input[*i] == '\'')
	{
		str = check_quot(input, i, input[*i], cp_env);
		if (!str)
			return (NULL);
	}
		j = *i;
		while (input[*i] && input[*i] != '>' && input[*i] != '<'
			&& input[*i] != '|' && input[*i] != ' ' && input[*i] != '"'
			&& input[*i] != '\'')
			(*i)++;
		if (j != *i)
		{
			//yaaaahhh 9awlbtek ma 9ltche lek kantchikiw hta variables yak ma 4at3awdi tchofo strdup hihihi
			if (str)
			{
				char	*sub = ft_substr(input, j, *i - j);
				char	*var = ft_var(sub, cp_env, input[*i]);
				char *s = ft_strjoin(str, var);
				free(str);
				free (sub);
				free(var);
				str = s;
				// free(s);
			}
			else
			{
				char	*sub = ft_substr(input, j, *i - j);
				char	*var = ft_var(sub, cp_env, input[*i]);
				str = ft_strdup(var);
				if (input[*i] == '"')
				{
					char	*quot = check_quot(input, i, input[*i], cp_env);
					if (quot)
					{
						char *s = ft_strjoin(str, quot);
						free(str);
						str = s;
						free (quot);
					}
					else
						return (NULL);
					// free(s);
				}
				free (sub);
				free(var);
			}
			if (str)
			{
				add_ch(&div, "string", str);
				free(str);
			}
			else
			{
				if (div)
					free(div);
				return (NULL);
			}
		}
		else if (j == *i && str)
		{
			add_ch(&div, "string", str);
			free(str);
		}
	return (div);
}

t_div	*ft_div(char *input, char **cp_env)
{
	int		i;
	t_div	*div;// ha nti zin ana 39lti 3liya ylah dizi teht

	i = 0;
	div = NULL;
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (!input[i] && ft_strlen(input) == 0)
			exit(1);
		if (input[i] == '|' || input[i] == '>' || input[i] == '<')
		{
			div = ft_operator(input, &i, div);// iwa ya lfasia hna kanchofo dakchi dyal hok hik hihihi z3ema itijahat tfo ma kaynche imoge
			if (!div)
				return (NULL);
		}
		else
		{
			div = ft_str(input, &i, div, cp_env); //saliti mn li lfo9 b3da bache tchofo hadi ha ha haaaaaaaa
			if (!div)
				return (NULL);
		}
	}
	return (div);
}
