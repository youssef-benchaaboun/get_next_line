#include "get_next_line.h"
int	ft_strlen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

void	ft_strcat(char *result, char *s)
{
	int	i;
	int	j;

	i = 0;
	if (!s)
		return ;
	while (result[i])
		i++;
	j = 0;
	while (s[j] && s[j] != '\n')
	{
		result[i + j] = s[j];
		j++;
	}
	if (s[j])
		result[(i++) + j] = s[j];
	result[i + j] = '\0';
}

void	ft_strcpy(char *dest, char *src)
{
	int		i;
	int ls;

	i = 0;
	if (!src)
		return ;
	ls=ft_strlen(src);
	src = src + ls;
	if (*src == '\n')
	{	ls++;
		src++;
	}
	while (src[i])
		i++;
	while (i>=0)
	{
		dest[i] = src[i];
		i--;
	}
	i =0;
	while(dest[i+ls+1])
		dest[i+(ls++)]='\0';
}

char	*ft_strjoin(char *r, char *s)
{
	char	*result;
	int		lr;
	int		ls;

	ls = ft_strlen(s);
	lr = ft_strlen(r);
	if (s[ft_strlen(s)])
		ls++;
	result = malloc((ls + lr + 1) * sizeof(char));
	result[0] = '\0';
	ft_strcat(result, r);
	ft_strcat(result, s);
	if (r)
		free(r);
	return (result);
}

int	handel_rest(char *rest, char **result)
{
	int end;

	end=0;
	if (rest[0])
	{
		*result = ft_strjoin(*result, rest);
		if ((*result)[ft_strlen(*result)] == '\n')
			end=1;
		ft_strcpy(rest, rest);
	}
	return (end);
}
