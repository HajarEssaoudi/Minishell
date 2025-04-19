#include "lib/libft.h"

char    *cv_var(char *str)
{
    int i = 0;
    while(str[i] != '$')
        i++;
    i++;
    while (str[i] && (str[i] == '~' || str[i] == '=' || str[i] == '^'))
        i++;
    if (str[i] && !(ft_isdigit(str[i])))
    {
        int j = i;
        while ((ft_isalpha(str[i]) || str[i] == '_') && str[i])
            i++;
        char *var = ft_substr(str, j, i - j);
        return var;
    }
    return NULL;
}

char    *ft_var(char *str)
{
    char *var = cv_var(str);

    char *g_var;
    int s = ft_strlen(str) + 1;
    int i = 0;
    int j = 0;
    if (var != NULL)
    {
        while (str[i] && str[i] != '$')
            i++;
        while (str[i] && str[i] != ' ')
        {
            i++;
            j++;
        }
        int v = (s - j) + ft_strlen(var);
        g_var = malloc (sizeof(char *) * v);
    }
    else
        g_var = malloc (sizeof(char *) * s);
    i = 0;
    j = 0;
    while (str[i])
    {
        if (var != NULL)
        {
            while (str[i] && str[i] != '$')
                g_var[j++] = str[i++];
            int k = 0;
            while (var[k])
                g_var[j++] = var[k++];
            while (str[i] && (str[i] != ' ' || str[i] != '-'))
                i++;
        }
        g_var[j++] = str[i++];
    }
    return g_var;
}

