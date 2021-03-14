/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 14:15:05 by user42            #+#    #+#             */
/*   Updated: 2021/03/14 13:54:11 by user42           ###   ########.fr       */
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
	if (!(*line = ft_calloc(BUFFER_SIZE * lfactor + 1, sizeof(char))))
		return (-1);
	i = 0;
	while ((b = read(STDIN, buf, 1)) >= 0)
	{
		if (b == 0)
		{
			if (!ft_strlen(*line))
			{
				ft_putstr_fd("exit", STDERR);
				exit(g_var.g_exitstatus);
			}
			continue ;
		}
		if (i == BUFFER_SIZE * lfactor && extendline(line, ++lfactor) == -1)
			return (-1);
		if (buf[0] == '\n')
			break ;
		(*line)[i++] = buf[0];
	}
	if (b == -1)
		return (-1);
	return (0);
}
