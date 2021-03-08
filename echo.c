/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 13:13:32 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/08 23:02:13 by user42           ###   ########.fr       */
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
	echo(t_list *argv, t_list **aenv)
{
	int			nl;
	t_list		*current;

	(void)aenv;
	current = argv;
	nl = 1;
	while (current && isvalidoption(gettokenstr(current)))
	{
		nl = optionnl(gettokenstr(current));
		current = current->next;
	}
	while (current)
	{
		write(STDOUT, gettokenstr(current), ft_strlen(gettokenstr(current)));
		current = current->next;
		if (current)
			write(STDOUT, " ", 1);
	}
	if (nl)
		write(STDOUT, "\n", 1);
	return (0);
}
