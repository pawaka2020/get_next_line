#include "get_next_line.h"

char	*ft_getrawline(int fd, char *left_str, int size)
{
	char	*buff;
	int		readres;

	buff = malloc(size + 1);
	if (!buff)
		return (0);
	readres = 1;
	while (ft_nlpresent(left_str) == 0 && readres !=0 )
	{
		readres = read(fd, buff, size);
		if (readres == -1)
		{
			free(buff);
			return (0);
		}
		buff[readres] = '\0';
		left_str = ft_append(left_str, buff);
	}
	free(buff);
	return (left_str);
}

//In case of empty feed, the previous function
//returns a string of 1 size, but element \0
char *ft_prenl(char *rawline)
{
	int i;
	int j;
	char *line;

	i = 0;

	if(rawline[i] == '\0')
		return (0);
	while (rawline[i] && rawline[i] != '\n')
		i++;
	if (rawline[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (0);	
	j = -1;
	while (j++, j != i)
		line[j] = rawline[j];
	line[j] = '\0';
	return(line);
}

char *ft_postnl(char *rawline)
{
	char *line;
	int i;
	int j;
	
	if (!rawline)
		return (0);
	i = 0;
	while (rawline[i] && rawline[i] != '\n')
		i++;
	if (rawline[i] == '\n')
		i++;
	line = malloc((ft_strlen(rawline) - i) + 1);
	if (!line)
		return (0);
	j = 0;
	while (rawline[i])
		line[j++] = rawline[i++];
	line[j] = '\0';
	free(rawline);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*rawline;
	int	size;
	
	#ifdef BUFFER_SIZE
		size = BUFFER_SIZE;
	#else
		size = 1;
	#endif
	if (fd < 0 || size <= 0)
		return (0);
	rawline = ft_getrawline(fd, rawline, size);
	if (!rawline)
		return (0);
	line = ft_prenl(rawline);
	rawline = ft_postnl(rawline);

	return (line);
}

// int	main()
// {
// 	int fd1 = open("text", O_RDONLY);
// 	int fd2 = open("text2", O_RDONLY);
// 	printf("Hello\n");
// 	// char *str = "123\n456";
// 	// printf("result = %s\n", before_nl(str));
// }