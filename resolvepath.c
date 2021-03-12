/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolvepath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 17:44:23 by user42            #+#    #+#             */
/*   Updated: 2021/03/12 17:38:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	removedot(char *rpath)
{
	char	*pdotdot;

	while ((pdotdot = ft_strnstr(rpath, "/.", ft_strlen(rpath)))
	&& pdotdot[2] != '.')
		loopcollapsestr(pdotdot, 0, 2);
}

static void
	doubleslash(char *rpath)
{
	if (rpath[4] == '/' && rpath[5] == '/' && rpath[6] == '/')
		while (rpath[5] == '/')
			collapsestr(rpath, 5);
}

void
	resolvepath(char *rpath)
{
	char	*pdotdot;
	char	*pprevdir;
	char	*tmp;
	char	*cwd;

	if (!(cwd = getcwd(NULL, 0)))
		return ;
	free(cwd);
	removedot(rpath);
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
	doubleslash(rpath);
}
