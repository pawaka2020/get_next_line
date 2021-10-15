/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riramli <riramli@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 00:00:00 by kolim             #+#    #+#             */
/*   Updated: 2021/04/26 00:00:00 by kolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_nlpresent(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		i++;
		if (str[i] == '\n')
			return (1);
	}	
	return (0);
}

int	ft_strlen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_append(char *src, char *dst)
{
	int		i;
	int		j;
	char	*newbuffer;

	i = 0;
	j = 0;
	newbuffer = malloc(ft_strlen(src) + ft_strlen(dst) + 1);
	if (!newbuffer)
		return (0);
	while (src && src[i])
	{
		newbuffer[i] = src[i];
		i++;
	}
	while (dst && dst[j])
	{
		newbuffer[i] = dst[j];
		i++;
		j++;
	}
	newbuffer[i] = '\0';
	free (src);
	return (newbuffer);
}
