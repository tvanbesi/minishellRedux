/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 17:16:14 by user42            #+#    #+#             */
/*   Updated: 2021/03/12 17:33:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	resetnullcwd(char **cwd, t_list *env)
{
	t_list	*env_pwd;

	env_pwd = findenv(env, "PWD");
	if (!*cwd)
	{
		if (!env)
		{
			if (!(*cwd = ft_strdup("")))
				return (-1);
		}
		else if (!(*cwd = ft_strdup(getenvval(env_pwd))))
			return (-1);
	}
	return (0);
}

int
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
	if (!ft_strlen(*path))
		return (0);
	return (1);
}

int
	findoldpwd(char **path, t_list **aenv, int *opoldpwd)
{
	t_list	*env;

	if (!(env = findenv(*aenv, "OLDPWD")) || !getenvval(env))
	{
		puterror(ERROR_NOOLDPWD);
		return (-3);
	}
	if (!(*path = ft_strdup(getenvval(env))))
		return (-1);
	*opoldpwd = 1;
	return (0);
}

int
	setabspwdenv(t_list **aenv, char *path)
{
	char	*pwdenv;
	size_t	l;

	l = ft_strlen(path) + 1 + 4;
	if (!(pwdenv = malloc(l + 1)))
		return (-1);
	ft_strlcpy(pwdenv, "PWD=", l + 1);
	ft_strlcat(pwdenv, path, l + 1);
	resolvepath(pwdenv);
	if (addenv(aenv, pwdenv) == -1)
	{
		free(pwdenv);
		return (-1);
	}
	free(pwdenv);
	return (0);
}

int
	setrelpwdenv(t_list **aenv, char **cwd, char *path)
{
	char	*pwdenv;
	size_t	l;

	if (resetnullcwd(cwd, *aenv) == -1)
		return (-1);
	l = ft_strlen(*cwd) + ft_strlen(path) + 1 + 4;
	if (!(pwdenv = malloc(l + 1)))
		return (-1);
	ft_strlcpy(pwdenv, "PWD=", l + 1);
	ft_strlcat(pwdenv, *cwd, l + 1);
	ft_strlcat(pwdenv, "/", l + 1);
	ft_strlcat(pwdenv, path, l + 1);
	resolvepath(pwdenv);
	if (addenv(aenv, pwdenv) == -1)
	{
		free(pwdenv);
		return (-1);
	}
	free(pwdenv);
	return (0);
}
