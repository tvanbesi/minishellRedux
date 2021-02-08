/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readstdin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 14:54:19 by user42            #+#    #+#             */
/*   Updated: 2021/02/08 12:34:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	extendline(char **line, t_readstdindata *rd)
{
	rd->lenfactor++;
	rd->len = BUFFER_SIZE * rd->lenfactor;
	rd->tmp = *line;
	*line = malloc(rd->len);
	if (!*line)
	{
		free(rd->tmp);
		return (-1);
	}
	ft_bzero(line, rd->len);
	ft_strlcpy(*line, rd->tmp, rd->len);
	free(rd->tmp);
	return (0);
}

static void
	initrd(t_readstdindata *rd)
{
	rd->lenfactor = 1;
	rd->len = BUFFER_SIZE;
	rd->buf[1] = '\0';
}

char
	*readstdin(void)
{
	char			*line;
	t_readstdindata	rd;
	size_t			b;

	line = malloc(BUFFER_SIZE);
	if (!line)
		return (NULL);
	initrd(&rd);
	ft_bzero(line, rd.len);
	b = read(STDIN, rd.buf, 1);
	while (b > 0)
	{
		if (rd.buf[0] == '\n')
			return (line);
		else if (ft_strlcat(line, rd.buf, rd.len) >= rd.len)
		{
			if (extendline(&line, &rd) == -1)
				return (NULL);
		}
		b = read(STDIN, rd.buf, 1);
	}
	if (b == 0)
	{
		write(STDOUT, "exit", 4);
		exit(EXIT);
	}
	else
		return (NULL);
}
