#include <stdio.h>
//read, malloc, free
//read is in 
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

//always remember to null-close a string when you add chars one by one. 
char	*append(char *buffer, char c, int *len)
{
	int	i;
	char *newbuffer;

	i = 0;
	newbuffer = malloc(*len + 2);
	if (*len != 0)
	{
		while (buffer[i])
		{
			newbuffer[i] = buffer[i];
			i++;
		}	
	}
	newbuffer[i] = c;
	newbuffer[i+1] = '\0';
	*len = *len + 1;
	return (newbuffer);
}

char *get_next_line(int fd)
{
	char *buffer;
	int len;
	char c;
	int readresult;

	len = 0;
	readresult = 1;
	//c = '\0';
	// while (read(fd, &c, 1) && (c != '\n'))
	// {
	// 	buffer = append(buffer, c, &len);
	// }
	while ((readresult = read(fd, &c, 1)) && (c != '\n'))
	{
		if (readresult == -1)
			return (0);
		else
			buffer = append(buffer, c, &len);
	}
	return (buffer);


}

//it's ok to use open here because fd will not be provided by us, it's provided by the test function which will not be submitted to moulinette
int main(void) 
{

	int fd = open("text", O_RDONLY);
	printf("Output:\n");
	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
	//char c;
	//printf("%ld\n", read(fd, &c, 1));
}