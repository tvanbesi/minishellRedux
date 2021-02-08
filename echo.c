/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 13:13:32 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/02/08 13:48:32 by user42           ###   ########.fr       */
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
	echo(char **argv, t_list **aenv)
{
	int			nl;
	int			i;

	(void)aenv;
	nl = optionnl(argv[0]);
	if (nl)
		i = 0;
	else
		i = 1;
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
