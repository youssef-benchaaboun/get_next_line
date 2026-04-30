#define BUFFER_SIZE 3
#include"get_next_line.h"
int ft_strlen(char *s)
{


	if(!s)
		return 0;
	int i=0;
	while(s[i] && s[i] !='\n')
		i++;
	return i;
}
void ft_strcat(char *result, char *s)
{
	int i;
	int j;
	i=0;
	while(result[i])
		i++;
	j=0;
	while(s2[i] && s2[j] !='\n')
	{
		result[i+j]=s2[j];
		j++;
	}
}

char * ft_strjoin(char *r,char *s)
{
	char *result;
	int lr;
	int ls;
	ls=ft_strlen(s);
	lr=ft_strlen(r);
	result=calloc((ls+lr+1)*sizeof(char));
	ft_strcat(result,r);
	free(r);
	ft_strcat(result,s);
	return result;
}

char *get_next_line(int fd)
{
	static char *rest=NULL;
	char *result="";
	if(fd<0 || BUFFER_SIZE<1)
		return NULL;
	char s[BUFFER_SIZE+1];
	if(result)
		
	while(new && read(fd,s[BUFFER_SIZE -1],BUFFER_SIZE-1))
	{
		result=ft_strjoin(result,s);
		new=ft_rest(rest,s);
	}
	return rest;
}



