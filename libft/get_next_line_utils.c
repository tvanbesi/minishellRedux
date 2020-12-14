/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 23:49:35 by tvanbesi          #+#    #+#             */
/*   Updated: 2019/11/26 17:08:58 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void
	ft_strncat(char *dst, const char *src, size_t n)
{
	while (*dst)
		dst++;
	while (n-- > 0)
		*dst++ = *src++;
	*dst = '\0';
}

static size_t
	ft_strlen(const char *s)
{
	size_t	r;

	r = 0;
	while (*s++)
		r++;
	return (r);
}

ssize_t
	ft_strnlchr(const char *s, size_t ofs)
{
	ssize_t	r;
	size_t	n;

	s += ofs;
	n = BUFFER_SIZE - ofs;
	r = 0;
	while (n-- > 0)
	{
		if (*s++ == '\n')
			return (r);
		r++;
	}
	return (-1);
}

char
	*ft_strxtd(char *line, const char *buf, size_t n)
{
	char	*r;
	size_t	l;

	l = line ? ft_strlen(line) : 0;
	if (!(r = (char*)malloc(l + n + 1)))
	{
		free(line);
		return (NULL);
	}
	*r = '\0';
	if (line)
	{
		ft_strncat(r, line, l);
		free(line);
	}
	ft_strncat(r, buf, n);
	return (r);
}

int
	ft_clear(t_buf *tbuf, int r)
{
	free(tbuf->buf);
	tbuf->buf = NULL;
	tbuf->ofs = 0;
	tbuf->ltr = 0;
	return (r);
}
