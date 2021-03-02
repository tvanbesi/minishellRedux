/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenvdata.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 20:02:13 by user42            #+#    #+#             */
/*   Updated: 2021/03/02 20:08:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	appendenv(char *input, char **val, char **name, t_list **aenv)
{
	t_list	*env;
	char	*tmp;

	if (!(*val = ft_strdup(&(*val)[1])))
		return (-1);
	if (!(*name = ft_substr(input, 0,
	ft_strlen(input) - (ft_strlen(*val) + 2))))
		return (-1);
	if ((env = findenv(*aenv, *name)) && getenvval(env))
	{
		tmp = *val;
		if (!(*val = ft_strjoin(getenvval(env), *val)))
			return (-1);
		free(tmp);
	}
	return (0);
}

int
	getenvdata(char *input, char **val, char **name, t_list **aenv)
{
	if (!(*val = ft_strchr(input, '=')))
	{
		*val = NULL;
		if (!(*name = ft_strdup(input)))
			return (-1);
	}
	else
	{
		if (*val - ft_strchr(input, '+') == 1)
		{
			if (appendenv(input, val, name, aenv) == -1)
				return (-1);
		}
		else
		{
			if (!(*val = ft_strdup(&(*val)[1])))
				return (-1);
			if (!(*name = ft_substr(input, 0,
			ft_strlen(input) - (ft_strlen(*val) + 1))))
				return (-1);
		}
	}
	return (0);
}
