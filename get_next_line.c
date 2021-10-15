/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riramli <riramli@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 00:00:00 by kolim             #+#    #+#             */
/*   Updated: 2021/04/26 00:00:00 by kolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//from other
size_t	ftt_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ftt_get_line(char *left_str)
{
	// variable declarations
	int		i;
	char	*str;
	i = 0;

	// null handling
	if (!left_str[i])
		return (NULL);

	// move i to position of \n in left_str
	while (left_str[i] && left_str[i] != '\n')
		i++;

	// create new string, size same as position of \n but with 2 extra
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);

	//copy from left_str to str, last is \n, then null terminate.
	i = 0;
	while (left_str[i] && left_str[i] != '\n')
	{
		str[i] = left_str[i];
		i++;
	}
	if (left_str[i] == '\n')
	{
		str[i] = left_str[i];
		i++;
	}
	str[i] = '\0';

	return (str);
}

char	*ftt_new_left_str(char *left_str)
{
	int		i;
	int		j;
	char	*str;
	i = 0;
	while (left_str[i] && left_str[i] != '\n')
		i++;
	if (!left_str[i])
	{
		free(left_str);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ftt_strlen(left_str) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (left_str[i])
		str[j++] = left_str[i++];
	str[j] = '\0';
	free(left_str);
	return (str);
}

char	*ftt_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ftt_strlen(s)]);

	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ftt_strjoin(char *left_str, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!left_str)
	{
		left_str = (char *)malloc(1 * sizeof(char));
		left_str[0] = '\0';
	}
	if (!left_str || !buff)
		return (NULL);
	str = malloc(sizeof(char) * ((ftt_strlen(left_str) + ftt_strlen(buff)) + 1));
	if (str == NULL)
		return (NULL);

	i = -1;
	j = 0;
	if (left_str)
		while (left_str[++i] != '\0')
			str[i] = left_str[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ftt_strlen(left_str) + ftt_strlen(buff)] = '\0';
	free(left_str);
	return (str);
}

char	*ftt_read(int fd, char *left_str, int size)
{
	char	*buff;
	int		rd_bytes;
	buff = malloc((size + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	
	rd_bytes = 1;
	while (!ftt_strchr(left_str, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, size);
		if (rd_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[rd_bytes] = '\0';
		left_str = ftt_strjoin(left_str, buff);
	}

	free(buff);
	return (left_str);
}


//end

char	*ft_getrawline(int fd, char *left_str, int size)
{
	char	*buff;
	int		readres;

	buff = malloc(size + 1);
	if (!buff)
		return (0);
	readres = 1;
	while (ft_nlpresent(left_str) == 0 && readres != 0)
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
	free (buff);
	return (left_str);
}

//In case of empty feed, the previous function
//returns a string of 1 size, but element \0
char	*ft_prenl(char *rawline)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	if (rawline[i] == '\0')
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
	return (line);
}

char	*ft_postnl(char *rawline)
{
	char	*line;
	int		i;
	int		j;

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
	free (rawline);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*rawline;
	int			size;

	size = BUFFER_SIZE;
	if (fd < 0 || size <= 0)
		return (0);
	//rawline = ftt_read(fd, rawline, size);
	rawline = ft_getrawline(fd, rawline, size);
	if (!rawline)
		return (0);
	//line = ftt_get_line(rawline);
	line = ft_prenl(rawline);
	//rawline = ftt_new_left_str(rawline);
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
