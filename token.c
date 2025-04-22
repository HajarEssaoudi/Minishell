#include "minishell.h"

t_tok   *ft_token(t_div *div)
{
    t_div   *cur;
    t_tok   *token;
    char    *st = NULL;
    cur = div;
    token = malloc (sizeof(t_tok));
    ft_memset(token, 0, ft_strlen(token));
    while (cur)
    {
        if (cur->type == "string" && (st != "pip" || !st))
        {
            token->cmd = ft_strdup(cur->args);
            st = cur->type;
        }
        else if (st == "string" && cur->type == "string")
        {
            token->str = ft_strdup(cur->args);
            st = cur->type;
        }
        else if ((st == "output" || st == "input" || st == "append" || st == "heredoc") && cur->type == "string")
        {
            token->str = ft_strdup(cur->filename);
            st = cur->type;
        }
        else if (cur->type = "output")
        {
            token->output = ft_strdup(cur->args);
            st = cur->type;
        }
        else if (cur->type = "input")
        {
            token->input = ft_strdup(cur->args);
            st = cur->type;
        }
        else if (cur->type = "append")
        {
            token->append = ft_strdup(cur->args);
            st = cur->type;
        }
        else if (cur->type = "heredoc")
        {
            token->heredoc = ft_strdup(cur->args);
            st = cur->type;
        }
        else if (cur->type = "pip")
        {
            token->pip = ft_strdup(cur->args);
            st = cur->type;
        }
        div = div->next;
    }
    return (token);
}
