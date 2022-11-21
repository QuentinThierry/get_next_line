/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 01:10:02 by qthierry          #+#    #+#             */
/*   Updated: 2022/11/21 02:55:51 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	copy_array(char	(*dest)[], char	(*src)[], size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		(*dest)[i] = (*src)[i];
		i++;
	}
}

char	*get_a_line(int fd, t_buf_list **list, ssize_t read_size)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*tmp;

	copy_array(&buffer, &(*list)->string, BUFFER_SIZE + 1);
	while (read_size)
	{
		tmp = ft_strchr(buffer, '\n');
		if (tmp)
		{
			//printf("test ici : %ld\n", (tmp - buffer + 1));
			if (!lst_add_back(list, buffer, read_size, read_size))
				return (NULL);
			return (NULL);
		}
		else
		{
			if (!lst_add_back(list, buffer, read_size, read_size))
				return (NULL);
			read_size = read(fd, buffer, BUFFER_SIZE);
			buffer[read_size] = 0;
		}
	}
	return (NULL);
}

void	get_new_buffer(t_buf_list **list)
{
	t_buf_list	*tmp;
	size_t		size;
	char		*new_line;

	while ((*list)->next)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
	}
	new_line = ft_strchr((*list)->string, '\n');
	if (new_line)
	{
		size = new_line - (*list)->string; // 17
		ft_memmove((*list)->string, (*list)->string + size + 1, (*list)->length);
		((*list)->string)[(*list)->length - size + 1] = 0;
		//printf("buffer ici length ? : %ld\n", (*list)->length);
	}
}

char	*get_next_line(int fd)
{
	static t_buf_list	*res_list = NULL;
	char				tmp_buffer[BUFFER_SIZE + 1];
	char				*res;
	ssize_t				read_size;

	read_size = BUFFER_SIZE;
	//printf("buffer ? : %s, %ld\n", res_list->string);
	if (!res_list)
	{
		read_size = read(fd, tmp_buffer, BUFFER_SIZE);
		if (read_size < 1)
			return (NULL);
		tmp_buffer[read_size] = 0;
		res_list = lst_new(tmp_buffer, read_size, read_size);
		if (!res_list)
			return (NULL);
	}
	else
		read_size = res_list->length;
	get_a_line(fd, &res_list, read_size);
	if (!res_list)
		return (NULL);
	res = list_to_str(res_list); //protect
	get_new_buffer(&res_list);
	//printf("buffer ? : %s\n", res_list->string);
	//printf("nouveau buffer : '%s'\n", res_list->string);
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
	free(line);
	close(fd);
	return 0;
}
