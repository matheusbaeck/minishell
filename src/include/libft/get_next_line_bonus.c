/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <santi.mag777@student.42madrid    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 22:44:29 by smagniny          #+#    #+#             */
/*   Updated: 2023/11/30 13:12:36 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//read(int fd, void *buf, size_t count);
char	*next(char	*buffer)
{	
	char	*newbuffer;
	int		i;
	int		j;
	int		l;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == 0)
	{
		free(buffer);
		return (NULL);
	}
	i++;
	l = ft_strlen(buffer) - i + 1;
	newbuffer = ft_calloc(l, sizeof(char));
	while (buffer[i] != '\0' && buffer[i] && j < l)
		newbuffer[j++] = buffer[i++];
	free(buffer);
	return (newbuffer);
}

char	*readalot(int fd, char *buffer)
{
	char	*tmpbuffer;
	int		bytecount;

	if (!buffer)
		buffer = ft_calloc(1, 1);
	tmpbuffer = ft_calloc(BUFFER_SIZE, sizeof(char));
	if (!tmpbuffer)
		return (NULL);
	bytecount = 1;
	while (bytecount)
	{
		bytecount = read(fd, tmpbuffer, BUFFER_SIZE);
		if (bytecount == -1)
		{
			free(tmpbuffer);
			break ;
		}
		tmpbuffer[bytecount] = 0;
		buffer = ft_strjoinfrees1(buffer, tmpbuffer);
		if (find_occurrence(tmpbuffer, '\n'))
			break ;
	}
	free(tmpbuffer);
	return (buffer);
}

char	*parse_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc((i + 2), sizeof(char));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*get_next_line(int fd)
{	
	static char	*buffer[FD_INDEX];
	char		*str;

	if (fd < 0 || BUFFER_SIZE <= 0 || (read(fd, 0, 0) < 0))
	{
		return (NULL);
	}
	buffer[fd] = readalot(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	str = parse_line(buffer[fd]);
	buffer[fd] = next(buffer[fd]);
	return (str);
}
