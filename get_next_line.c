#include"get_next_line.h"
char	*get_next_line(int fd)
{
	static char	s[BUFFER_SIZE + 1];
	char		*result;
	int		control;

	result = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (handel_rest(s, &result))
		return (result);
	control = read(fd, s, BUFFER_SIZE);
	while (control > 0)
	{
		s[control] = '\0';
		result = ft_strjoin(result, s);
		if (s[ft_strlen(s)] == '\n')
			break ;
		control = read(fd, s, BUFFER_SIZE);
	}
	if (control == -1)
		return (NULL);
	ft_strcpy(s, s);
	return (result);
}
#include <stdio.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("get_next_line.c", O_RDONLY);
	if (fd < 0)
		return (1);

	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}

	close(fd);
	return (0);
}
