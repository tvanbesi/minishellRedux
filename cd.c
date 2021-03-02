/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 13:07:04 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/02 05:40:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	setpwdenv(t_list **aenv, char *newcwd)
{
	char		*wd;
	char		*tmpwd;
	char		*oldpwd;
	char		*newpwd;
	t_list		*env;

	if (!(wd = getcwd(NULL, 0)))
	{
		if ((env = findenv(*aenv, "PWD")))
		{
			if (!(tmpwd = ft_strdup(getenvval(env))))
				return (-1);
		}
		else if (!(tmpwd = ft_strdup("")))
			return (-1);
		if (!ft_strncmp(newcwd, ".", 2))
		{
			if (!(wd = ft_strjoin(tmpwd, "/.")))
				return (-1);
		}
		else if (!(wd = ft_strdup("")))
			return (-1);
		free(tmpwd);
	}
	if (!(newpwd = ft_strjoin("PWD=", wd)))
	{
		free(wd);
		return (-1);
	}
	free(wd);
	if ((env = findenv(*aenv, "PWD")))
	{
		if (!(tmpwd = ft_strdup(getenvval(env))))
			return (-1);
	}
	else if (!(tmpwd = ft_strdup("")))
		return (-1);
	if (!(oldpwd = ft_strjoin("OLDPWD=", tmpwd)))
	{
		free(tmpwd);
		return (-1);
	}
	if (addenv(aenv, oldpwd) == -1)
	{
		free(tmpwd);
		free(newpwd);
		return (-1);
	}
	free(tmpwd);
	if (addenv(aenv, newpwd) == -1)
	{
		free(newpwd);
		return (-1);
	}
	free(newpwd);
	return (0);
}

int
	cd(char **argv, t_list **aenv)
{
	t_list		*home;
	char		*tmp;

	if (!argv[0])
	{
		if (!(home = findenv(*aenv, "HOME")))
		{
			puterror(ERROR_NOHOME);
			return (-2);
		}
		if (chdir(getenvval(home)) == -1)
			return (-1);
		else if (setpwdenv(aenv, "") == -1)
			return (-1);
	}
	else if (argv[1])
	{
		puterror(ERROR_TOO_MANY_ARG);
		return (-1);
	}
	else
	{
		if (!argv[0][0])
		{
			if (chdir(".") == -1)
				return (-1);
			else if (setpwdenv(aenv, ".") == -1)
				return (-1);
			return (0);
		}
		if (chdir(argv[0]) == -1)
			return (-1);
		if (argv[0][0] == '/' && argv[0][1] == '/' && argv[0][2] != '/')
		{
			if (!argv[0][2])
			{
				if (setpwdenv(aenv, argv[0]) == -1)
					return (-1);
				if (addenv(aenv, "PWD=//") == -1)
					return (-1);
			}
			else if (argv[0][2] != '/')
			{
				if (setpwdenv(aenv, argv[0]) == -1)
					return (-1);
				if (!(tmp = ft_strjoin("PWD=", argv[0])))
					return (-1);
				if (addenv(aenv, tmp) == -1)
				{
					free(tmp);
					return (-1);
				}
				free(tmp);
			}
		}
		else if (setpwdenv(aenv, argv[0]) == -1)
			return (-1);
	}
	return (0);
}
