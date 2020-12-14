/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:58:02 by tvanbesi          #+#    #+#             */
/*   Updated: 2019/11/26 19:12:57 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int
	make_next_line(int fd, char **line, t_buf *tbuf)
{
	ssize_t		pnl;
	ssize_t		b;
	size_t		n;

	if (tbuf->ltr == -1)
		return (0);
	while ((pnl = ft_strnlchr(tbuf->buf, tbuf->ofs)) == -1)
	{
		n = tbuf->ltr ? tbuf->ltr : BUFFER_SIZE - tbuf->ofs;
		if (!(*line = ft_strxtd(*line, tbuf->buf + tbuf->ofs, n)))
			return (-1);
		tbuf->ofs = 0;
		if (!(b = read(fd, tbuf->buf, BUFFER_SIZE)))
			return (0);
		else if (b < BUFFER_SIZE)
			tbuf->ltr = b;
	}
	n = (tbuf->ltr && tbuf->ltr < pnl) ? tbuf->ltr : pnl;
	*line = ft_strxtd(*line, tbuf->buf + tbuf->ofs, n);
	if (n && n == (size_t)tbuf->ltr)
		return (0);
	if (tbuf->ltr)
		tbuf->ltr = tbuf->ltr - (n + 1) == 0 ? -1 : tbuf->ltr - (n + 1);
	tbuf->ofs += n + 1;
	return (1);
}

int
	get_next_line(int fd, char **line)
{
	static t_buf	tbuf;
	ssize_t			b;
	int				mnl;

	if (!BUFFER_SIZE || !line || read(fd, NULL, 0) == -1
		|| !(*line = ft_strxtd(NULL, NULL, 0)))
		return (-1);
	if (!(tbuf.buf))
		if (!(tbuf.buf = (char*)malloc(BUFFER_SIZE)))
			return (-1);
	b = 0;
	if (tbuf.ofs || (b = read(fd, tbuf.buf, BUFFER_SIZE)))
	{
		if (b && b < BUFFER_SIZE)
			tbuf.ltr = (size_t)b;
		if ((mnl = make_next_line(fd, line, &tbuf)) == 1)
			return (1);
		else if (mnl == 0)
			return (ft_clear(&tbuf, 0));
		else
			return (-1);
	}
	else
		return (ft_clear(&tbuf, 0));
}
