/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 01:13:21 by qthierry          #+#    #+#             */
/*   Updated: 2022/11/19 19:58:10 by qthierry         ###   ########.fr       */
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

t_buf_list	*lst_new(const char *content, size_t length)
{
	t_buf_list	*res;

	if (!content)
		return (NULL);
	res = malloc(sizeof(t_buf_list));
	if (!res)
		return (NULL);
	ft_memmove(res->string, content, length);
	res->length = length;
	res->next = NULL;
	return (res);
}

int	lst_add_back(t_buf_list **list, const char *content, size_t length)
{
	t_buf_list	*tmp;
	t_buf_list	*added;

	added = lst_new(content, length);
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
	size_t		m_size;
	t_buf_list	*start;

	if (!list)
		return (NULL);
	start = list;
	m_size = 0;
	while (list->next)
	{
		m_size += list->length;
		list = list->next;
	}
	list = start;
	res = malloc(sizeof(char) * (m_size + 1));
	if (!res)
		return (NULL);
	m_size = 0;
	while (list->next)
	{
		ft_memmove(res + m_size, list->string, list->length);
		m_size += list->length;
		list = list->next;
	}
	printf("tst : %s\n", res);
	return (res);
}
