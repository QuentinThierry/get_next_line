/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 01:09:59 by qthierry          #+#    #+#             */
/*   Updated: 2022/11/19 03:05:15 by qthierry         ###   ########.fr       */
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

char	*ft_strchr(const char *s, int c);
char	*ft_realloc(char *src, size_t size);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_memmove(void *dest, const void *src, size_t n);

# endif