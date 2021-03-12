/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 13:07:04 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/12 16:55:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	findhome(char **path, t_list **aenv)
{
	t_list	*env;

	if (!(env = findenv(*aenv, "HOME")) || !getenvval(env))
	{
		puterror(ERROR_NOHOME);
		return (-3);
	}
	if (!(*path = ft_strdup(getenvval(env))))
		return (-1);
	return (0);
}

static int
	findoldpwd(char **path, t_list **aenv)
{
	t_list	*env;

	if (!(env = findenv(*aenv, "OLDPWD")) || !getenvval(env))
	{
		puterror(ERROR_NOOLDPWD);
		return (-3);
	}
	if (!(*path = ft_strdup(getenvval(env))))
		return (-1);
	return (0);
}

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

int
	cd(t_list *argv, t_list **aenv)
{
	char		*path;
	int			okcd;
	int			opoldpwd;
	int			r;

	path = NULL;
	okcd = 1;
	opoldpwd = 0;
	if (!argv)
	{
		if ((r = findhome(&path, aenv)) < 0)
			return (r);
		if (!ft_strlen(path))
			return (0);
	}
	else if (argv->next)
		return (toomanyarg());
	else if (!ft_strncmp(gettokenstr(argv), "-", 2))
	{
		if ((r = findoldpwd(&path, aenv)) < 0)
			return (r);
		opoldpwd = 1;
	}
	else if ((r = setpath(&path, gettokenstr(argv), &okcd)) == -1)
		return (-1);
	if ((okcd && chdir(path) == -1) || updatepwd(aenv, path) == -1)
	{
		free(path);
		return (-1);
	}
	if (opoldpwd)
		ft_putendl_fd(path, STDOUT);
	free(path);
	return (r);
}
