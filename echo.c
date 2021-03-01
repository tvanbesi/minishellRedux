/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 13:13:32 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/02/28 14:38:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	optionnl(char **argv)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		if (argv[i][0] == '-')
		{
			if (argv[i][1] == 'n')
				return (0);
		}
		else
			return (1);
		i++;
	}
	return (1);
}

int
	echo(char **argv, t_list **aenv)
{
	int			nl;
	int			i;

	(void)aenv;
	nl = optionnl(argv);
	i = 0;
	while (argv[i] && argv[i][0] == '-')
		i++;
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
