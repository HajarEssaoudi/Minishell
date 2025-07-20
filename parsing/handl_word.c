/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 01:39:53 by mabdelha          #+#    #+#             */
/*   Updated: 2025/07/20 23:55:24 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parsing.h"

void	add_split2(t_split *split, t_split *new_split)
{

	t_split	*tmp;
	tmp = split;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_split;
}

void	add_split(t_split **split, char *str, int quoted, char *flag)
{
	t_split	*tmp;
	int l;

	tmp = malloc(sizeof(t_split));
	l = 0;
	if (str)
		tmp->str = ft_strdup(str);
	else
		tmp->str = ft_strdup("");
	tmp->quoted = quoted;
	tmp->first_space = 0;
	tmp->last_space = 0;
	tmp->flag = flag;
	tmp->next = NULL;
	if (str)
	{
		l = ft_strlen(str);
		if (str[0] == ' ' && !quoted)
			tmp->first_space = 1;
		if (str[l - 1] == ' ' && !quoted)
			tmp->last_space = 1;
	}
	if (!*split || !split)
	{
		*split = tmp;
	}
	else
		add_split2(*split, tmp);
}

t_lexer	*ft_final(t_lexer *lexer, t_split *split)
{
char *final;
char *tmp;
char *amg = "0";
char **final_split;
int i;
t_split	*fin_split;

fin_split = split;  
final = NULL;  
while(fin_split)  
{
	if (fin_split->quoted)  
	{  
		if (final)  
		{  
			tmp = ft_strjoin(final, fin_split->str);  
			free(final);  
			final = tmp;  
		}  
		else  
		{  
			if (final)  
				free(final);  
			final = ft_strdup(fin_split->str);  
		}  
	}
	else  
	{  
		final_split = ft_split(fin_split->str, ' ');
		if (!fin_split->quoted && !ft_strcmp(fin_split->flag, "2"))
		{
			int count = 0;
			while (final_split[count])
				count++;
			if (count > 1)
				amg = "3";
		}  
		if (fin_split->first_space && fin_split->last_space)  
		{ 
			if(final)  
			{  
				add_ch(&lexer, "string", final, amg);  
				free(final); 
				final = ft_strdup("");
			}
			i = 0;
			while(final_split[i])  
			{
				add_ch(&lexer, "string", final_split[i], amg);  
				i++;  
			}  
			free_str(final_split);  
		}  
		else if (!fin_split->first_space && fin_split->last_space)  
		{  
			if (final)  
			{  
				tmp = ft_strjoin(final, final_split[0]);  
				add_ch(&lexer, "string", tmp, amg);  
				free(final);  
				free(tmp);  
				final = ft_strdup("");
			}  
			else if (final_split[0])  
			{  
				add_ch(&lexer, "string", final_split[0], amg);  
			}  
			i = 1;  
			while(final_split[i])  
			{  
				add_ch(&lexer, "string", final_split[i], amg);  
				i++;  
			}  
			free_str(final_split);  
		}  
		else if (fin_split->first_space && !fin_split->last_space)  
		{  
			if(final)  
			{  
				add_ch(&lexer, "string", final, amg);  
				free(final);  
				final = ft_strdup("");
			}  
			int j = 0;  
			while(final_split[j])  
				j++;  
			i = 0;  
			while(final_split[i] && i < j - 1)  
			{  
				add_ch(&lexer, "string", final_split[i], amg);  
				i++;  
			}  
			if (j > 0 && final_split[j - 1])  
			{  
				if (final)  
					free(final);  
				final = ft_strdup(final_split[j - 1]);  
			}  
			free_str(final_split);  
		}  
		else  
		{  
			if (final && final_split[0])  
			{  
				tmp = ft_strjoin(final, final_split[0]);  
				free(final);  
				final = tmp;  
			}  
			else if (final_split[0])
			{  
				if (final)  
					free(final);  
				final = ft_strdup(final_split[0]);  
			}  
			  
			int j = 0;  
			while(final_split[j])  
				j++;  
			i = 1;  
			while(final_split[i] && i < j - 1)  
			{  
				add_ch(&lexer, "string", final_split[i], amg);  
				i++;  
			}
			if (j > 1 && final_split[j - 1])  
			{  
				if (final)  
				{  
					add_ch(&lexer, "string", final, amg); 
					// tmp = ft_strjoin(final, final_split[j - 1]);  
					free(final);  
					final = ft_strdup(final_split[j - 1]);  
				}  
				else  
				{  
					if (final)  
						free(final);  
					final = ft_strdup(final_split[j - 1]);  
				}  
			}  
			free_str(final_split);  
		}  
	}  
	fin_split = fin_split->next;  
}  
 
if (final)  
{
	add_ch(&lexer, "string", final, amg);
	free(final);
}  
// if (final)  
// 	free(final);  
  
return lexer;

}

t_lexer	*get_str(char *input, t_lexer *lexer, char **cp_env, char *flag)
{
	int i = 0;
	t_split *split = NULL;
	char *tmp1 = NULL;
	char *tmp2 = NULL;
	char *tmp = NULL;
	char *var_qout = NULL;
	char *var = NULL;
	int k = 0;
	int j;
	char quot;

	// printf("input => %s\n", input);
	while (input[i])
	{
		j = i;
		if (input[i] == '"' || input[i] == '\'')
		{
			quot = input[i];
			i++;
			j = i;
			while (input[i] && input[i] != quot)
				i++;
			if (!input[i])
			{
				printf("Minishell: syntax error: unclosed `%c' quote\n", quot);
				return NULL;
			}
			var_qout = ft_substr(input, j, i - j);
			i++;
			if (quot == '"')
			{
				tmp1 = ft_strdup("");
				k = 0;
				while (var_qout[k])
				{
					if (var_qout[k] == '$' && (ft_isalpha(var_qout[k + 1]) || var_qout[k + 1] == '_') && ft_strcmp(flag, "1"))
					{
						// int start = k;
						// while (start > 0 && var_qout[start - 1] != '$')
						// 	start--;

						// if (start < k)
						// {
						// 	tmp2 = ft_substr(var_qout, start, k - start);
						// 	tmp = ft_strjoin(tmp1, tmp2);
						// 	free(tmp1);
						// 	tmp1 = tmp;
						// }
						k++;
						int var_start = k;
						while (var_qout[k] && (ft_isalnum(var_qout[k]) || var_qout[k] == '_'))
							k++;
						char *varname = ft_substr(var_qout, var_start, k - var_start);
						char *val = ft_var(varname, cp_env);
						tmp = ft_strjoin(tmp1, val);
						free(tmp1);
						tmp1 = tmp;
					}
					else
					{
						int start = k;
						while (var_qout[k] && var_qout[k] != '$')
						{
							if (var_qout[k] == '$' && ((!ft_isalpha(var_qout[k + 1]) || var_qout[k + 1] != '_') || !ft_strcmp(flag, "1")))
								k++;
							else
								k++;
						}
							// k++;
						tmp2 = ft_substr(var_qout, start, k - start);
						tmp = ft_strjoin(tmp1, tmp2);
						free(tmp1); free(tmp2);
						tmp1 = tmp;
					}
				}
				add_split(&split, tmp1, 1, flag);
				free(tmp1); free(var_qout);
			}
			else
			{
				add_split(&split, var_qout, 1, flag);
				free(var_qout);
			}
		}
		else
		{
			while (input[i] && input[i] != '"' && input[i] != '\'')
				i++;
			var = ft_substr(input, j, i - j);
			tmp1 = ft_strdup("");
			k = 0;
			while (var[k])
			{
				if (var[k] == '$' && (ft_isalpha(var[k + 1]) || var[k + 1] == '_') && ft_strcmp(flag, "1"))
				{
					int start = k;
					k++;
					int var_start = k;
					while (var[k] && (ft_isalnum(var[k]) || var[k] == '_'))
						k++;
					tmp2 = ft_substr(var, var_start, k - var_start);
					char *val = ft_var(tmp2, cp_env);
					tmp = ft_strjoin(tmp1, val);
					free(tmp1);
					tmp1 = tmp;
					// free(tmp2);
				}
				else
				{
					int start = k;
					while (var[k] && var[k] != '$')
					{
						if (var[k] == '$' && ((!ft_isalpha(var[k + 1]) || var[k + 1] != '_') || !ft_strcmp(flag, "1")))
							k++;
						else
							k++;
					}
					// k++;
					tmp2 = ft_substr(var, start, k - start);
					tmp = ft_strjoin(tmp1, tmp2);
					free(tmp1); free(tmp2);
					tmp1 = tmp;
				}
			}
			// printf("tmp1 ===> %s\n", tmp1);
			add_split(&split, tmp1, 0, flag);
			free(tmp1); free(var);
		}
	}
	// t_split *spl = split;
	// while (spl)
	// {
	// 	printf("spl->str ==> %s\n", spl->str);
	// 	spl = spl->next;
	// }
	
	lexer = ft_final(lexer, split);
	return lexer;
}
