#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

char    **ft_div(char *input)
{
    char    **div;
    int i;

    while (input[i])
        i++;
    *div = malloc(sizeof(char *) * (i + 1));
    i = 0;
    while (input[i] == ' ')
        i++;
    int j = 0;
    while (input[i])
    {
        while (input[i] != ' ')
        {
            div[j] = input[i];
            i++;
            j++;
        }
        i++;
    }
    return div;
}