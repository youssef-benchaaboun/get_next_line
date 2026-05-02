#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H
#ifndef BUFFER_SIZE 
	#define BUFFER_SIZE 5
#endif
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
char    *get_next_line(int fd);
int     ft_strlen(char *s);
void    ft_strcat(char *result, char *s);
void    ft_strcpy(char *dest, char *src);
char    *ft_strjoin(char *r, char *s);
int     handel_rest(char *rest, char **result);
#endif
