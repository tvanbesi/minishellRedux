/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 13:13:32 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/02 20:32:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	isvalidoption(char *s)
{
	int	i;

	if (!s || s[0] != '-')
		return (0);
	i = 1;
	while (s[i])
		if (!ft_isalnum(s[i++]))
			return (0);
	if (i == 1)
		return (0);
	return (1);
}

static int
	optionnl(char *argv)
{
	int	i;
	int	r;

	i = 0;
	r = 1;
	while (argv[i])
	{
		if (argv[0] == '-' && argv[i] == 'n')
			r = 0;
		i++;
	}
	return (r);
}

int
	echo(char **argv, t_list **aenv)
{
	int			nl;
	int			i;

	(void)aenv;
	i = 0;
	while (isvalidoption(argv[i]))
		nl = optionnl(argv[i++]);
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
