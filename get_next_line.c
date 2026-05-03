#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			bytes;

	line = NULL;
	if (read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (handle_rest(buffer, &line))
		return (line);
	bytes = read(fd, buffer, BUFFER_SIZE);
	while (bytes)
	{
		buffer[bytes] = '\0';
		line = ft_strjoin(line, buffer);
		if (buffer[ft_strlen(buffer)] == '\n')
			break ;
		bytes = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes == -1)
		return (free(line), (NULL));
	ft_strcpy(buffer, buffer);
	return (line);
}
