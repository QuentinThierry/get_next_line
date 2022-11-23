/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 01:10:02 by qthierry          #+#    #+#             */
/*   Updated: 2022/11/23 14:22:33 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	append_string(t_buf_list *list, char **res)
{
	char	*tmp;

	while (list)
	{
		tmp = ft_strchr(list->string, '\n');
		if (tmp)
		{
			ft_memmove((*res), list->string, (tmp - list->string) + 1);
			(*res)[(tmp - list->string) + 1] = 0;
			return (1);
		}
		ft_memmove((*res), list->string, list->length);
		(*res) += list->length;
		list = list->next;
	}
	return (0);
}

char	*list_to_str(t_buf_list *list)
{
	char		*res;
	char		*cpy;
	size_t		m_size;
	t_buf_list	*start;

	res = NULL;
	if (!list)
		return (NULL);
	m_size = 0;
	list = list->next;
	start = list;
	while (start)
	{
		m_size += start->length;
		start = start->next;
	}
	res = malloc(sizeof(char) * (m_size + 1));
	cpy = res;
	if (!append_string(list, &res))
		cpy[m_size] = 0;
	return (cpy);
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
	static t_static	buffer[16];
	char			*res;
	ssize_t			read_size;

	res_list = NULL;
	if (BUFFER_SIZE == 0)
		return (NULL);
	if(read(fd, NULL, 0) == -1)
		return (NULL);
	read_size = buffer[fd].read_size;
	if (buffer[fd].string[0] == 0)
	{
		read_size = read(fd, buffer[fd].string, BUFFER_SIZE);
		if (read_size < 1)
			return (NULL);
	}
	if(!lst_add_back(&res_list, buffer[fd].string, read_size))
		return (NULL);
	get_a_line(fd, &res_list, read_size, &buffer[fd]);
	res = list_to_str(res_list);
	if (!res)
		return (NULL);
	get_new_buffer(&res_list, &buffer[fd]);
	return (free(res_list), res);
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

// int main(void)
// {
// 	char	*line;
// 	int		fd;

// 	fd = open("test.txt", O_RDWR);
// 	line = get_next_line(fd);
// 	printf("resultat1 : '%s'\n", line);
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("resultat2 : '%s'\n", line);
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("resultat3 : '%s'\n", line);
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("resultat4 : '%s'\n", line);
// 	free(line);
// 	close(fd);
// 	return 0;
// }
