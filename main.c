#include "minishell.h"

typedef struct s_div
{
    char            *args;
    char            *type;
    struct s_div    *next;
}                   t_div;

int size_env(char **env)
{
    int i;

    i = 0;
    while (env[i])
        i++;
    return (i);
}

void    free_div(t_div *div)
{
    t_div    *tmp;

    tmp = div;
    while (div)
    {
        tmp = div;
        div = div->next;
        free(tmp->args);
        free(tmp->type);
        free(tmp);
    }
}

char    *get_env_var(char **cp_env, char *key)
{
    int        i;
    size_t    len;

    i = 0;
    len = ft_strlen(key);
    while (cp_env[i])
    {
        if (ft_strncmp(cp_env[i], key, len) == 0 && cp_env[i][len] == '=')
            return (&cp_env[i][len + 1]);
        i++;
    }
    return (NULL);
}

char    **cop_env(char **env)
{
    int        size;
    char    **cp_env;
    int        i;
    int        j;

    size = size_env(env) + 1;
    cp_env = malloc(sizeof(char *) * size);
    i = 0;
    j = 0;
    while (env[i])
    {
        cp_env[j++] = ft_strdup(env[i++]);
    }
    cp_env[j] = NULL;
    return (cp_env);
}

char    *cv_var(char *str)
{
    int        i;
    int        j;
    char    *var;

    i = 0;
    while (str[i] != '$')
        i++;
    i++;
    while (str[i] && (str[i] == '~' || str[i] == '=' || str[i] == '^'))
        i++;
    if (str[i] && !(ft_isdigit(str[i])))
    {
        j = i;
        while ((ft_isalpha(str[i]) || str[i] == '_') && str[i])
            i++;
        var = ft_substr(str, j, i - j);
        return (var);
    }
    else if (str[i] && ft_isdigit(str[i]))
        return ("1");
    return (NULL);
}

char    *ft_var(char *str, char **cp_env)
{
    int        i;
    char    *result;
    char    *val;
    char    *tmp;
    int        start;
    char    *key;
    char    tmp_char[2] = {0};
    char    *tmp_result;

    i = 0;
    result = malloc(1);
    result[0] = '\0';
    while (str[i])
    {
        if (str[i] == '~' && (i == 0 || str[i - 1] == ' ') && (str[i + 1] == '/'
                || str[i + 1] == '\0' || str[i + 1] == ' '))
        {
            val = get_env_var(cp_env, "HOME");
            tmp = ft_strjoin(result, val ? val : "");
            free(result);
            result = tmp;
            i++;
        }
        else if (str[i] == '$')
        {
            i++;
            if (str[i] == '{')
            {
                i++;
                start = i;
                while (str[i] && str[i] != '}')
                    i++;
                if (str[i] == '}')
                {
                    key = ft_substr(str, start, i - start);
                    val = get_env_var(cp_env, key);
                    tmp = ft_strjoin(result, val ? val : "");
                    free(result);
                    result = tmp;
                    free(key);
                    i++;
                }
            }
            else if (ft_isalpha(str[i]) || str[i] == '_')
            {
                start = i;
                while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
                    i++;
                key = ft_substr(str, start, i - start);
                val = get_env_var(cp_env, key);
                tmp = ft_strjoin(result, val ? val : "");
                free(result);
                result = tmp;
                free(key);
            }
        }
        else
        {
            tmp_char[0] = str[i];
            tmp_char[1] = '\0';
            tmp_result = ft_strjoin(result, tmp_char);
            free(result);
            result = tmp_result;
            i++;
        }
    }
    return (result);
}

void    add_ch(t_div **div, char *type, char *input)
{
    t_div    *token;
    t_div    *tmp;

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

t_div    *ft_div(char *input, char **cp_env)
{
    int        i;
    t_div    *div;
    char    *str;
    int        j;

    i = 0;
    div = NULL;
    while (input[i])
    {
        while (input[i] == ' ')
            i++;
        if (!input[i])
            exit(1);
        if (input[i] == '|')
        {
            if (check_pip(input))
            {
                return (NULL);
            }
            else
            {
                add_ch(&div, "pip", "|");
                i++;
            }
        }
        else if (input[i] == '>' && input[i + 1] != '>')
        {
            if (check_redirect(input))
                return (NULL);
            add_ch(&div, "redirect_out", ">");
            i++;
        }
        else if (input[i] == '<' && input[i + 1] != '<')
        {
            if (check_redirect(input))
                return (NULL);
            add_ch(&div, "redirect_in", "<");
            i++;
        }
        else if (input[i] == '>' && input[i + 1] == '>')
        {
            if (check_redirect2(input))
                return (NULL);
            add_ch(&div, "redirect_out", ">>");
            i++;
        }
        else if (input[i] == '<' && input[i + 1] == '<')
        {
            if (check_redirect2(input))
                return (NULL);
            add_ch(&div, "redirect_in", "<<");
            i++;
        }
        else if (input[i] == '"' || input[i] == '\'')
        {
            str = check_quot(input, &i, input[i], cp_env);
            if (str)
            {
                add_ch(&div, "string", str);
                free(str);
            }
            else
                return (NULL);
        }
        else
        {
            j = i;
            while (input[i] && input[i] != '>' && input[i] != '<'
                && input[i] != '|' && input[i] != ' ' && input[i] != '"' && input[i] != '\'')
                i++;
            if (input[i])
            {i--;
                str = ft_strdup(ft_var(ft_substr(input, j, i - j), cp_env));
                add_ch(&div, "string", str);
                free(str);
                i++;
            }
        }
    }
    return (div);
}

int    main(int argc, char **argv, char **env)
{
    char **cp_env = cop_env(env);
    while (1)
    {
        char *l = readline("Minishell>> ");
        t_div *div;
        div = ft_div(l, cp_env);
        if (div != NULL)
        {
            t_div *tmp = div;
            while (tmp)
            {
                printf("%s => %s\n", tmp->args, tmp->type);
                tmp = tmp->next;
            }
        }
        else
            free_div(div);
        add_history(l);
        free(l);
    }
    return (0);
}