/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 14:15:05 by user42            #+#    #+#             */
/*   Updated: 2021/03/13 10:46:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	extendline(char **line, int lfactor)
{
	char	*tmp;

	tmp = *line;
	if ((*line = malloc(BUFFER_SIZE * lfactor + 1)))
		ft_strlcpy(*line, tmp, BUFFER_SIZE * lfactor + 1);
	free(tmp);
	if (!*line)
		return (-1);
	return (0);
}

int
	prompt(char **line)
{
	ssize_t	b;
	int		i;
	int		lfactor;
	char	buf[1];

	lfactor = 1;
	if (!(*line = malloc(BUFFER_SIZE * lfactor + 1)))
		return (-1);
	i = 0;
	while ((b = read(STDIN, buf, 1)) > 0)
	{
		if (i == BUFFER_SIZE * lfactor && extendline(line, ++lfactor) == -1)
			return (-1);
		if (buf[0] == '\n')
			break ;
		(*line)[i++] = buf[0];
	}
	(*line)[i] = '\0';
	if (b == 0 && !(*line)[0])
	{
		write(STDERR, "exit", 4);
		exit(g_var.g_exitstatus);
	}
	b = b == -1 ? b : 0;
	return (b);
}
