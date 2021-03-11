/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolvepath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 17:44:23 by user42            #+#    #+#             */
/*   Updated: 2021/03/11 19:34:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	resolvepath(char *rpath)
{
	char	*pdotdot;
	char	*pprevdir;
	char	*tmp;

	while ((pdotdot = ft_strnstr(rpath, "/..", ft_strlen(rpath))))
	{
		pprevdir = ft_strchr(rpath, '/');
		tmp = pprevdir;
		if (pprevdir == pdotdot)
			loopcollapsestr(pprevdir, 0, 3);
		else
		{
			while ((tmp = ft_strchr(tmp + 1, '/')) < pdotdot)
				pprevdir = tmp;
			loopcollapsestr(pprevdir, 0, pdotdot - pprevdir + 3);
		}
	}
	if (!ft_strchr(rpath, '/'))
		ft_strlcat(rpath, "/", 6);
	if (rpath[4] == '/' && rpath[5] == '/' && rpath[6] == '/')
	{
		while (rpath[5] == '/')
			collapsestr(rpath, 5);
	}
}
