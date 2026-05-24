/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoben-ch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 19:37:49 by yoben-ch          #+#    #+#             */
/*   Updated: 2026/05/21 19:37:49 by yoben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	if (!src)
		return ;
	while (src[i] && src[i] != '\n')
	{
		dest[i] = src[i];
		i++;
	}
	if (src[i])
		dest[i++] = '\n';
	dest[i] = '\0';
}

void	ft_shift(char *buffer)
{
	int	skip;
	int	i;

	i = 0;
	skip = ft_strlen(buffer);
	if (buffer[skip])
		skip++;
	while (buffer[skip])
		buffer[i++] = buffer[skip++];
	while (i < BUFFER_SIZE)
		buffer[i++] = '\0';
}

char	*ft_strjoin(char *line, char *buffer)
{
	char	*joined;
	int		ll;
	int		bl;

	bl = ft_strlen(buffer);
	ll = ft_strlen(line);
	if (buffer[bl])
		bl++;
	joined = malloc((bl + ll + 1) * sizeof(char));
	if (!joined)
		return (free(line), NULL);
	ft_strcpy(joined, line);
	ft_strcpy(joined + ll, buffer);
	if (line)
		free(line);
	return (joined);
}
