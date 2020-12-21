/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 13:13:32 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/21 14:50:00 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	optionnl(char *arg)
{
	size_t	i;

	if (!arg)
		return (1);
	if (arg[0] != '-')
		return (1);
	if (!arg[1])
		return (1);
	i = 1;
	while (arg[i])
		if (arg[i++] != 'n')
			return (1);
	return (0);
}

int
	echo(char **argv)
{
	int			nl;
	int			i;

	nl = optionnl(argv[0]);
	i = nl ? 0 : 1;
	while (argv[i])
	{
		write(STDOUT, argv[i], ft_strlen(argv[i]));
		i++;
		if (argv[i])
			write(STDOUT, " ", 1);
	}
	if (nl)
		write(STDOUT, "\n", 1);
	return (0);
}
