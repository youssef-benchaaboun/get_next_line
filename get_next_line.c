/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoben-ch <yoben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 19:37:49 by yoben-ch          #+#    #+#             */
/*   Updated: 2026/05/29 17:50:13 by yoben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[GNL_BUFFER_SIZE + 1];
	char		*line;
	int			bytes;

	line = NULL;
	if (BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	bytes = 1;
	if (!buffer[0])
		bytes = read(fd, buffer, BUFFER_SIZE);
	while (bytes > 0)
	{
		line = ft_strjoin(line, buffer);
		ft_shift(buffer);
		if (!line)
			return (NULL);
		if (line[ft_strlen(line)])
			break ;
		bytes = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes < 0)
		return (free(line), (NULL));
	return (line);
}
