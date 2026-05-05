#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif
#ifndef OPEN_MAX
# define OPEN_MAX 1024
#endif
# include <stdlib.h>
# include <unistd.h>
#include <limits.h>

char	*get_next_line(int fd);
int		ft_strlen(char *s);
void	ft_strcpy(char *rest, char *buffer);
void	ft_shift(char *buffer);
char	*ft_strjoin(char *line, char *buffert);
#endif
