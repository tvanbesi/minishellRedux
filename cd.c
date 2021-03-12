/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 13:07:04 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/12 17:16:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	setpath(char **path, char *argv, int *okcd)
{
	if (!ft_strncmp(argv, ".", 2) && !(*path = getcwd(NULL, 0)))
	{
		*okcd = 0;
		puterror(strerror(errno));
		if (!(*path = ft_strdup(".")))
			return (-1);
		return (-3);
	}
	else if (!ft_strncmp(argv, "..", 3) && !(*path = getcwd(NULL, 0)))
	{
		puterror(strerror(errno));
		if (!(*path = ft_strdup("..")))
			return (-1);
		return (-3);
	}
	else
	{
		if (*path)
			free(*path);
		if (!(*path = ft_strdup(argv)))
			return (-1);
	}
	if (!ft_strlen(*path))
		*okcd = 0;
	return (0);
}

static int
	toomanyarg(void)
{
	puterror(ERROR_TOO_MANY_ARG);
	return (-3);
}

static int
	ret(char *s)
{
	free(s);
	return (-1);
}

static void
	initparsedata(t_parsedata *pd)
{
	pd->opoldpwd = 0;
	pd->okcd = 1;
	pd->r = 0;
}

int
	cd(t_list *argv, t_list **aenv)
{
	char		*path;
	t_parsedata	pd;

	path = NULL;
	initparsedata(&pd);
	if (!argv)
	{
		if ((pd.r = findhome(&path, aenv)) <= 0)
			return (pd.r);
	}
	else if (argv->next)
		return (toomanyarg());
	else if (!ft_strncmp(gettokenstr(argv), "-", 2))
	{
		if ((pd.r = findoldpwd(&path, aenv, &pd.opoldpwd)) < 0)
			return (pd.r);
	}
	else if ((pd.r = setpath(&path, gettokenstr(argv), &pd.okcd)) == -1)
		return (-1);
	if ((pd.okcd && chdir(path) == -1) || updatepwd(aenv, path) == -1)
		return (ret(path));
	if (pd.opoldpwd)
		ft_putendl_fd(path, STDOUT);
	free(path);
	return (pd.r);
}
