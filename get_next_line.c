/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 01:10:02 by qthierry          #+#    #+#             */
/*   Updated: 2022/11/19 20:00:03 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_buf_list	*get_a_line(int fd, char *buffer)
{
	ssize_t		read_size;
	char		*tmp;
	char		*tmp2;
	t_buf_list	*list;

	list = NULL;
	if (buffer[0] == 0)
		read_size = read(fd, buffer, BUFFER_SIZE);
	while (read_size > 0)
	{
		tmp = ft_strchr(buffer, '\n');
		if (tmp)
		{
			tmp2 = malloc(sizeof(char) * read_size);
			ft_memmove(tmp2, buffer, read_size);
			printf("test ici : %s\n", tmp2);
			lst_add_back(&list, tmp2, (tmp - buffer));
			buffer += (tmp - buffer);
			return (list);
		}
		else
		{
			tmp2 = malloc(sizeof(char) * read_size);
			ft_memmove(tmp2, buffer, read_size);
			lst_add_back(&list, tmp2, read_size);
			buffer += read_size;
		}
		read_size = read(fd, buffer, BUFFER_SIZE);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE] = {0};
	t_buf_list	*res_list;
	char		*res;

	res_list = get_a_line(fd, buffer);
	if (!res_list)
		return (NULL);
	res = list_to_str(res_list);
	return (res);
}

int main(void)
{
	char	*line;
	int		fd;

	fd = open("test.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("resultat1 : '%s'\n", line);
	free(line);
	line = get_next_line(fd);
	printf("resultat2 : '%s'\n", line);
	free(line);
	line = get_next_line(fd);
	printf("resultat3 : '%s'\n", line);
	free(line);
	line = get_next_line(fd);
	printf("resultat4 : '%s'\n", line);
	
	close(fd);
	return 0;
}
