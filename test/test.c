#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Sample implementation of ft_strjoin_sep
char	*ft_strjoin_sep(char *s1, char *s2, char sep)
{
	int	len1;
	int	len2;

	len1 = strlen(s1);
	len2 = strlen(s2);
	char *res = malloc(len1 + len2 + 2); // +1 for sep +1 for \0
	if (!res)
		return (NULL);
	strcpy(res, s1);
	res[len1] = sep;
	strcpy(res + len1 + 1, s2);
	return (res);
}

char	*concatenate_args(char **str)
{
	char	*cnc_str;
	int		i;
	char	*tmp;

	i = 1;
	if (!str[i])
		return (NULL);
	cnc_str = strdup(str[i]);
	i++;
	while (str[i])
	{
		tmp = ft_strjoin_sep(cnc_str, str[i], ' ');
		free(cnc_str);
		cnc_str = tmp;
		i++;
	}
	return (cnc_str);
}

int	main(void)
{
	char	*str;

	char *args[] = {"program", "hajar", "essao", NULL};
	str = concatenate_args(args);
	if (str)
	{
		printf("%s\n", str);
		free(str);
	}
	return (0);
}
