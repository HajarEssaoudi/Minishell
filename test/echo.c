#include <stdio.h>
#include <stdlib.h>

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin_sep(char *s1, char *s2, char sep)
{
	int		i;
	int		j;
	char	*p;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	p = (char *)malloc(i + j + 1 + 1);
	if (!p)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = sep;
	i++;
	while (s2[j])
		p[i++] = s2[j++];
	p[i] = '\0';
	return (p);
}

char	*concatenate_args (char **str)
{
	char	*cnc_str;
	int		i;

	i = 1;
	while(str[i] && str[i + 1])
	{
		cnc_str = ft_strjoin_sep(str[i], str[i + 1], ' ');
		i++;
	}
	return (cnc_str);
}

int main()
{
	// char *args[] = {"hajar", "essao", NULL};
	// char *str = concatenate_args(args);
	char *str = ft_strjoin_sep("hajar", "esso", ',');
	printf ("%s\n", str);
}