//start of header
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
//put all the standard library includes here
//make sure to include "get_next_line.h" in the .c files
//for printf in main()
#include <stdio.h>
//for write in main()
#include <unistd.h>
//for write in main()
#include <fcntl.h>
//for malloc
#include <stdlib.h>
//prototypes from get_next_line_utils.c
//char	*append(char *buffer, char c, int *len);
int ft_nlpresent(char *str);
int	ft_strlen(char *s);
char	*ft_append(char *src, char *dst);
char	*ft_getrawline(int fd, char *left_str, int size);
char	*ft_prenl(char *rawline);
char	*ft_postnl(char *rawline);
char	*get_next_line(int fd);
//end of header
#endif