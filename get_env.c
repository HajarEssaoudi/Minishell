#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/libft.h"



int size_env(char **env)
{
  int i = 0;
  while (env[i])
    i++;
  return i;
}

char **cop_env(char **env)
{
  int size = size_env(env) + 1;
  char **cp_env = malloc(sizeof(char *) * size);

  int i = 0;
  int j = 0;
  while (env[i])
  {
    cp_env[j++] = ft_strdup(env[i++]);
  }
  cp_env[j] = NULL;
  return cp_env;
}

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
    } 
}

int main(int argc, char *argv[], char *envp[])
{
  int index = 0;
  char **cp_env = cop_env(envp);
  char *str;
  char *var = cv_var(str);
  int size = ft_strlen(var);
  if (var != NULL)
  {
    int i = 0;
    while (cp_env[i])
    {
      if(ft_strncmp (cp_env[i], var, size == 0 && cp_env[i][size] == '='))
        str = &cp_env[i][size];
      i++;
    }
  }
  
}
