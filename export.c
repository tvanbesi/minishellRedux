/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:52:33 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/14 09:08:25 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	isidentifiervalid(char *s)
{
	if (!ft_isalpha(*s++))
		return (0);
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
	t_list	*env;
	int		i;

	i = 0;
	while (argv[i])
	{
		if (!isidentifiervalid(argv[i]))
		{
			puterror(ERROR_INVALID_IDENTIFIER);
			return (-2);
		}
		if (addenv(aenv, argv[i++]) == -1)
			return (-1);
	}
	return (0);
}