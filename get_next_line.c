/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 01:10:02 by qthierry          #+#    #+#             */
/*   Updated: 2022/11/23 16:30:43 by qthierry         ###   ########.fr       */
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

int	get_a_line(int fd, t_buf_list **list)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	read_size;

	if (*list)
	{
		read_size = (*list)->length;
		copy_array(&buffer, &(*list)->string, (*list)->length);
	}
	else
		read_size = read(fd, buffer, BUFFER_SIZE);
	while (read_size > 0)
	{
		buffer[read_size] = 0;
		if (!lst_add_back(list, buffer, read_size))
			return (0);
		if (ft_strchr(buffer, '\n'))
			return (buffer[read_size] = 0, 1);
		read_size = read(fd, buffer, BUFFER_SIZE);
	}
	return (1);
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
		size = new_line - (*list)->string + 1;
		ft_memmove((*list)->string, \
			(*list)->string + size, (*list)->length - size + 1);
		(*list)->length -= size;
	}
	else
	{
		free(*list);
		*list = NULL;
	}

}

char	*get_next_line(int fd)
{
	static t_buf_list	*res_list = NULL;
	char				*res;

	if (BUFFER_SIZE == 0)
		return (NULL);
	if(read(fd, NULL, 0) == -1)
		return (NULL);
	if(!get_a_line(fd, &res_list))
		return (NULL);
	res = list_to_str(res_list);
	if (!res)
		return (NULL);
	get_new_buffer(&res_list);
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
