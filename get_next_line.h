/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 01:09:59 by qthierry          #+#    #+#             */
/*   Updated: 2022/11/19 19:40:11 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef G_N_L
# define G_N_L

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
# endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct s_buf_list
{
	char			string[BUFFER_SIZE];
	size_t			length;
	struct s_buf_list	*next;
}	t_buf_list;

char		*ft_strchr(const char *s, int c);
char		*ft_realloc(char *src, size_t size);
char		*ft_strjoin(char *s1, char *s2);
void		*ft_memmove(void *dest, const void *src, size_t n);
size_t		ft_strlen(const char *s);

t_buf_list	*lst_new(const char *content, size_t length);
int			lst_add_back(t_buf_list **list, const char *content, size_t length);
char	*list_to_str(t_buf_list	*list);

# endif
