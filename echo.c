/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 13:13:32 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/14 09:13:01 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char
	*getoption(char *arg)
{
	if (arg && arg[0] == '-')
		return (&arg[1]);
	return (NULL);
}

int
	echo(char **argv)
{
	char		*option;
	int			nl;
	int			i;

	nl = 1;
	if ((option = getoption(argv[0])) && ft_strchr(option, 'n'))
		nl = 0;
	i = option ? 1 : 0;
	while (argv[i])
	{
		if (write(STDOUT, argv[i], ft_strlen(argv[i])) == -1)
			return (-1);
		i++;
		if (argv[i] && (write(STDOUT, " ", 1) == -1))
			return (-1);
	}
	if (nl && (write(STDOUT, "\n", 1) == -1))
		return (-1);
	return (0);
}
