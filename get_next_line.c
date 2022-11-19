/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 01:10:02 by qthierry          #+#    #+#             */
/*   Updated: 2022/11/19 03:12:13 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_my_buffer(int fd, char **buffer)
{
	char	*total;
	char	*start;
	char	*tmp2;
	char	*tmp;
	size_t	size;
	
	total = NULL;
	size = 0;
	while (fd > 1)
	{
		start = *buffer;
		tmp2 = ft_strchr(*buffer, '\n');
		if (tmp2) // trouve une fin de ligne
		{
			size += tmp2 - start + 1;
			//printf("test : %ld\n", tmp2 - start + 1);
			tmp = malloc(sizeof(char) * (tmp2 - start + 1)); // protect
			ft_memmove(tmp, *buffer, (tmp2 - start));
			tmp[(tmp2 - start)] = 0;
			*buffer += (tmp2 - start + 1);
			total = ft_strjoin(total, tmp);
			free(tmp);
			return (total);
		}
		else 
		{
			size += BUFFER_SIZE;
			total = ft_strjoin(total, *buffer);
		}
		if (read(fd, *buffer, BUFFER_SIZE) == -1)
			return (NULL);
		(*buffer)[BUFFER_SIZE] = 0;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*res;

	if (!buffer)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		buffer[BUFFER_SIZE] = 0;
		buffer[0] = 0;
	}
	if (!buffer)
		return (NULL);
	res = get_my_buffer(fd, &buffer);
	return (res);
}



int main(void)
{
	char	*line;
	int		fd;

	fd = open("test.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("resultat : '%s'\n", line);
	free(line);
	line = get_next_line(fd);
	printf("resultat2 : '%s'\n", line);
	free(line);
	line = get_next_line(fd);
	printf("resultat2 : '%s'\n", line);
	free(line);
	line = get_next_line(fd);
	printf("resultat2 : '%s'\n", line);
	
	close(fd);
	return 0;
}
