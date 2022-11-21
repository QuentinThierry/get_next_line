/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 01:13:21 by qthierry          #+#    #+#             */
/*   Updated: 2022/11/21 18:37:47 by qthierry         ###   ########.fr       */
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

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (NULL);
	if (dest < src)
	{
		i = 0;
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	else
	{
		i = n;
		while (i-- > 0)
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
	}
	return (dest);
}

t_buf_list	*lst_new(const char *content, size_t read_size, size_t length)
{
	t_buf_list	*res;

	if (!content)
		return (NULL);
	res = malloc(sizeof(t_buf_list));
	if (!res)
		return (NULL);
	ft_memmove(res->string, content, read_size);
	res->string[read_size] = 0;
	res->length = length;
	res->next = NULL;
	return (res);
}

int	lst_add_back(t_buf_list **list, const char *content, size_t read_size, size_t length)
{
	t_buf_list	*tmp;
	t_buf_list	*added;

	if (!content || !*content)
		return (1);
	added = lst_new(content, read_size, length);
	if (!added)
		return (0);
	if (!*list)
	{
		*list = added;
		return (1);
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = added;
	return (1);
}

char	*list_to_str(t_buf_list *list)
{
	char		*res;
	char		*cpy;
	char		*tmp;
	size_t		m_size;
	size_t		size;
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
	while (list)
	{
		tmp = ft_strchr(list->string, '\n');
		if (tmp)
		{
			size = tmp - list->string;
			ft_memmove(res, list->string, size + 1);
			res[size + 1] = 0;
			return (cpy);
		}
		ft_memmove(res, list->string, list->length);
		res += list->length;
		list = list->next;
	}
	cpy[m_size] = 0;
	return (cpy);
}
