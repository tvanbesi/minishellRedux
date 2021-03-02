/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 13:07:04 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/02 16:31:20 by user42           ###   ########.fr       */
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
		return (-2);
	}
	if (!(*path = ft_strdup(getenvval(env))))
		return (-1);
	return (0);
}

static int
	setpath(char **path, char **cd_arg, char *argv)
{
	if (!argv[0])
	{
		if (!(*path = ft_strdup(".")))
			return (-1);
	}
	else
	{
		if (!(*path = ft_strdup(argv)))
			return (-1);
		*cd_arg = argv;
	}
	return (0);
}

static int
	exception(t_list **aenv, char *cd_arg)
{
	char	*tmp;
	int		r;

	if (!(tmp = ft_strjoin("PWD=", cd_arg)))
		return (-1);
	r = addenv(aenv, tmp);
	free(tmp);
	return (r);
}

int
	cd(char **argv, t_list **aenv)
{
	char		*path;
	char		*cd_arg;

	path = NULL;
	cd_arg = NULL;
	if (!argv[0])
	{
		if (findhome(&path, aenv) < 0)
			return (findhome(&path, aenv));
	}
	else if (argv[1])
	{
		puterror(ERROR_TOO_MANY_ARG);
		return (-1);
	}
	else if (setpath(&path, &cd_arg, argv[0]) == -1)
		return (-1);
	if (chdir(path) == -1)
		return (-1);
	free(path);
	if (setpwdenv(aenv, cd_arg) == -1)
		return (-1);
	if (cd_arg && cd_arg[0] == '/' && cd_arg[1] == '/' && cd_arg[2] != '/')
		return (exception(aenv, cd_arg));
	return (0);
}
