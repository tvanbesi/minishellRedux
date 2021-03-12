/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:30:09 by user42            #+#    #+#             */
/*   Updated: 2021/03/12 17:32:54 by user42           ###   ########.fr       */
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
	emptypwd(char **cwd)
{
	free(*cwd);
	if (!(*cwd = ft_strdup("")))
		return (-1);
	return (0);
}

static int
	findpwd(char *tmp, char **cwd, t_list *env)
{
	if ((tmp = getenvvalbyname(env, "PWD")))
	{
		free(*cwd);
		if (!(*cwd = ft_strdup(tmp)))
			return (-1);
		return (0);
	}
	return (1);
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
	tmp = NULL;
	if (path[0] == '/')
	{
		if ((setabspwdenv(aenv, path)) == -1)
			return (-1);
		return (0);
	}
	else if (!(cwd = getcwd(NULL, 0)))
		;
	else if ((r = findpwd(tmp, &cwd, *aenv)) <= 0)
		;
	else if (r == -1 || emptypwd(&cwd) == -1)
		return (-1);
	r = setrelpwdenv(aenv, &cwd, path);
	free(cwd);
	return (r);
}
