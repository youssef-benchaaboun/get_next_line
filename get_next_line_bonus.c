#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	buffer[OPEN_MAX][BUFFER_SIZE + 1];
	char		*line;
	int			bytes;

	line = NULL;
	if (read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buffer[fd][0])
		bytes = 1;
	else
		bytes = read(fd, buffer[fd], BUFFER_SIZE);
	while (bytes)
	{
		line = ft_strjoin(line, buffer[fd]);
		ft_shift(buffer[fd]);
		if (!line)
			return (NULL);
		if (line[ft_strlen(line)])
			break ;
		bytes = read(fd, buffer[fd], BUFFER_SIZE);
	}
	if (bytes == -1)
		return (free(line), (NULL));
	return (line);
}
