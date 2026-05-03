#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
int		ft_strlen(char *s);
int		ft_strlen_full(char *str);
void	ft_strcat(char *line, char *buffer);
void	ft_strcpy(char *rest, char *buffer);
char	*ft_strjoin(char *line, char *buffer);
int		handle_rest(char *rest, char **line);

#endif
