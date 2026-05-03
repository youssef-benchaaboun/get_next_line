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

void	ft_strcat(char *line, char *buffer)
{
	int	i;
	int	j;

	i = 0;
	if (!buffer)
		return ;
	while (line[i])
		i++;
	j = 0;
	while (buffer[j] && buffer[j] != '\n')
	{
		line[i + j] = buffer[j];
		j++;
	}
	if (buffer[j])
		line[(i++) + j] = buffer[j];
	line[i + j] = '\0';
}

void	ft_strcpy(char *rest, char *buffer)
{
	int	buffer_len;
	int	rest_len;
	int	i;

	buffer = buffer + ft_strlen(buffer);
	if (*buffer == '\n')
		buffer++;
	rest_len = 0;
	buffer_len = 0;
	i = 0;
	while (buffer[buffer_len])
		buffer_len++;
	while (rest[rest_len])
		rest_len++;
	while (i < rest_len)
	{
		if (i < buffer_len)
			rest[i] = buffer[i];
		else
			rest[i] = '\0';
		i++;
	}
}

char	*ft_strjoin(char *line, char *buffer)
{
	char	*joined;
	int		line_len;
	int		buffer_len;

	buffer_len = ft_strlen(buffer);
	line_len = ft_strlen(line);
	if (buffer[ft_strlen(buffer)])
		buffer_len++;
	joined = malloc((buffer_len + line_len + 1) * sizeof(char));
	if (!joined)
		return (NULL);
	joined[0] = '\0';
	ft_strcat(joined, line);
	ft_strcat(joined, buffer);
	if (line)
		free(line);
	return (joined);
}

int	handle_rest(char *rest, char **line)
{
	int	end;

	end = 0;
	if (rest[0])
	{
		*line = ft_strjoin(*line, rest);
		if (!(*line))
			end = 1;
		else if ((*line)[ft_strlen(*line)] == '\n')
			end = 1;
		ft_strcpy(rest, rest);
	}
	return (end);
}
