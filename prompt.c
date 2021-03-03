/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 14:15:05 by user42            #+#    #+#             */
/*   Updated: 2021/03/03 12:43:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	prompt(char **line)
{
	ssize_t	b;
	int		i;
	char	buf[1];

	if (!(*line = malloc(BUFFER_SIZE)))
		return (-1);
	i = 0;
	while ((b = read(STDIN, buf, 1)) > 0)
	{
		//Extend when necessary
		if (buf[0] == '\n')
			break ;
		(*line)[i++] = buf[0];
	}
	(*line)[i] = '\0';
	if (b == 0 && !(*line)[0])
	{
		write(STDERR, "exit", 4);
		exit(g_exitstatus);
	}
	if (b == -1)
		return (-1);
	return (0);
}
