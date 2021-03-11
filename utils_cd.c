/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:30:09 by user42            #+#    #+#             */
/*   Updated: 2021/03/11 19:18:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	setoldpwd(t_list **aenv, int quit)
{
	char	*opwd;
	char	*tmp;
	t_list	*env_pwd;
	size_t	l;

	if (!(env_pwd = findenv(*aenv, "PWD")))
		return (1);
	else if (!(tmp = getenvval(env_pwd)))
		return (1);
	l = ft_strlen(tmp) + 7;
	if (!(opwd = malloc(l + 1)))
		return (-1);
	ft_strlcpy(opwd, "OLDPWD=", l + 1);
	ft_strlcat(opwd, tmp, l + 1);
	if (addenv(aenv, opwd) == -1)
	{
		free(opwd);
		return (-1);
	}
	free(opwd);
	return (quit);
}

static int
	setabspwdenv(t_list **aenv, char *path)
{
	char	*pwdenv;
	size_t	l;

	l = ft_strlen(path) + 1 + 4;
	if (!(pwdenv = malloc(l + 1)))
		return (-1);
	ft_strlcpy(pwdenv, "PWD=", l + 1);
	ft_strlcat(pwdenv, path, l + 1);
	if (addenv(aenv, pwdenv) == -1)
	{
		free(pwdenv);
		return (-1);
	}
	free(pwdenv);
	return (0);
}

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

static int
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

int
	updatepwd(t_list **aenv, char *path)
{
	char	*cwd;
	char	*tmp;
	int		r;

	if ((r = setoldpwd(aenv, path[0] != '\0')) <= 0)
		return (r);
	cwd = NULL;
	if (path[0] == '/')
	{
		if ((setabspwdenv(aenv, path)) == -1)
			return (-1);
		return (0);
	}
	else if (!(cwd = getcwd(NULL, 0)))
		;
	else if ((tmp = getenvvalbyname(*aenv, "PWD")))
	{
		if (!(cwd = ft_strdup(tmp)))
			return (-1);
	}
	else if (!(cwd = ft_strdup("")))
		return (-1);
	r = setrelpwdenv(aenv, &cwd, path);
	free(cwd);
	return (r);
}
