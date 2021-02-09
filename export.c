/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:52:33 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/02/09 16:12:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	isidentifiervalid(char *s)
{
	if (!(ft_isalpha(*s) || *s == '_'))
		return (0);
	s++;
	while (*s && *s != '=')
	{
		if (!(ft_isalnum(*s) || *s == '_'))
			return (0);
		s++;
	}
	return (1);
}

int
	export(char **argv, t_list **aenv)
{
	int		i;
	int		r;

	i = 0;
	r = 0;
	while (argv[i])
	{
		if (!isidentifiervalid(argv[i]))
		{
			puterror(ERROR_INVALID_IDENTIFIER);
			r = -2;
		}
		else if (addenv(aenv, argv[i]) == -1)
			return (-1);
		i++;
	}
	return (r);
}
