/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 23:49:29 by tvanbesi          #+#    #+#             */
/*   Updated: 2019/11/26 16:08:00 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>

# define BUFFER_SIZE 4096

typedef struct		s_buf
{
	char			*buf;
	size_t			ofs;
	ssize_t			ltr;
}					t_buf;

char				*ft_strxtd(char *line, const char *buf, size_t n);
int					get_next_line(int fd, char **line);
ssize_t				ft_strnlchr(const char *s, size_t ofs);
int					ft_clear(t_buf *tbuf, int r);

#endif
