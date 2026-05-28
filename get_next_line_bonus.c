/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoben-ch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 19:37:49 by yoben-ch          #+#    #+#             */
/*   Updated: 2026/05/21 21:25:45 by yoben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	buffer[OPEN_MAX][GNL_BUFFER_SIZE + 1];
	char		*line;
	int			bytes;

	line = NULL;
	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, NULL, 0) < 0)
		return (buffer[fd][0] = '\0', NULL);
	bytes = 1;
	if (!buffer[fd][0])
		bytes = read(fd, buffer[fd], GNL_BUFFER_SIZE);
	while (bytes > 0)
	{
		line = ft_strjoin(line, buffer[fd]);
		ft_shift(buffer[fd]);
		if (!line)
			return (NULL);
		if (line[ft_strlen(line)])
			break ;
		bytes = read(fd, buffer[fd], GNL_BUFFER_SIZE);
	}
	if (bytes == -1)
		return (free(line), (NULL));
	return (line);
}
