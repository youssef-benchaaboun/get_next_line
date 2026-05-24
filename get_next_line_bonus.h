/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoben-ch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 19:37:49 by yoben-ch          #+#    #+#             */
/*   Updated: 2026/05/21 21:39:07 by yoben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif
# if BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif
# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
int		ft_strlen(char *s);
void	ft_strcpy(char *rest, char *buffer);
void	ft_shift(char *buffer);
char	*ft_strjoin(char *line, char *buffert);
#endif
