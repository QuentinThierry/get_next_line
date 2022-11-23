/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 01:10:02 by qthierry          #+#    #+#             */
/*   Updated: 2022/11/23 13:25:54 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == 0)
		return ((char *)s);
	return (NULL);
}

void	copy_array(char (*dest)[], char (*src)[], size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		(*dest)[i] = (*src)[i];
		i++;
	}
}

char	*get_a_line(int fd, t_buf_list **list, ssize_t read_size, t_static *res)
{
	char	*tmp;

	copy_array(&((*res).string), &(*list)->string, read_size + 1);
	while (read_size)
	{
		tmp = ft_strchr((*res).string, '\n');
		if (tmp)
		{
			if (!lst_add_back(list, (*res).string, read_size))
				return (NULL);
			return (NULL);
		}
		else
		{
			if (!lst_add_back(list, (*res).string, read_size))
				return (NULL);
			read_size = read(fd, (*res).string, BUFFER_SIZE);
			if (read_size < 1)
				return (NULL);
			(*res).string[read_size] = 0;
		}
	}
	return (NULL);
}

void	get_new_buffer(t_buf_list **list, t_static *buffer)
{
	t_buf_list	*tmp;
	size_t		size;
	char		*new_line;

	(*buffer).string[0] = 0;
	(*buffer).read_size = 0;
	while ((*list)->next)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
	}
	new_line = ft_strchr((*list)->string, '\n');
	if (new_line)
	{
		size = new_line - (*list)->string + 1;
		ft_memmove((*list)->string, \
			(*list)->string + size, (*list)->length - size + 1);
		(*list)->length -= size;
	}
	else
		return ;
	copy_array(&(*buffer).string, &(*list)->string, (*list)->length + 1);
	(*buffer).read_size = (*list)->length;
	return ;
}

char	*get_next_line(int fd)
{
	t_buf_list		*res_list;
	static t_static	buffer;
	char			*res;
	ssize_t			read_size;

	if (BUFFER_SIZE == 0)
		return (NULL);
	read_size = buffer.read_size;
	if (buffer.string[0] == 0)
	{
		read_size = read(fd, buffer.string, BUFFER_SIZE);
		if (read_size < 1)
			return (NULL);
	}
	res_list = lst_new(buffer.string, read_size);
	if (!res_list)
		return (NULL);
	get_a_line(fd, &res_list, read_size, &buffer);
	res = list_to_str(res_list);
	if (!res)
		return (NULL);
	get_new_buffer(&res_list, &buffer);
	free(res_list);
	return (res);
}

// int main(void)
// {
// 	char	*line;
// 	int		fd;

// 	fd = open("test.txt", O_RDONLY);
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("line : '%s'", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return 0;
// }

int main(void)
{
	char	*line;
	int		fd;

	fd = open("test.txt", O_RDWR);
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
