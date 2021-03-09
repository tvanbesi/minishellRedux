/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:30:09 by user42            #+#    #+#             */
/*   Updated: 2021/03/10 00:58:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	setoldpwd(t_list **aenv)
{
	char	*opwd;
	char	*tmp;
	t_list	*env_pwd;
	int		r;

	if (!(env_pwd = findenv(*aenv, "PWD")))
		return (0);
	r = 0;
	if (getenvval(env_pwd))
		opwd = ft_strdup(getenvval(env_pwd));
	else
		opwd = ft_strdup("");
	if (!opwd)
		return (-1);
	tmp = opwd;
	opwd = ft_strjoin("OLDPWD=", opwd);
	free(tmp);
	if (!opwd)
		return (-1);
	if ((r = addenv(aenv, opwd) == -1))
		puterror(strerror(errno));
	free(opwd);
	return (r);
}

static int
	setcwd(char **cwd, t_list *env_pwd, char *cd_arg)
{
	if (env_pwd)
	{
		if (getenvval(env_pwd) && !ft_strncmp(cd_arg, ".", 2))
			*cwd = ft_strjoin(getenvval(env_pwd), "/.");
		else
			*cwd = ft_strdup("");
		if (!*cwd)
			return (-1);
	}
	else
		*cwd = NULL;
	return (0);
}

int
	setpwdenv(t_list **aenv, char *cd_arg)
{
	char	*cwd;
	char	*tmp;
	t_list	*env_pwd;

	env_pwd = findenv(*aenv, "PWD");
	cwd = NULL;
	if (!(cwd = getcwd(NULL, 0)) && setcwd(&cwd, env_pwd, cd_arg) == -1)
		return (-1);
	if (!cwd)
		return (setoldpwd(aenv));
	tmp = cwd;
	cwd = ft_strjoin("PWD=", cwd);
	free(tmp);
	if (!cwd)
		return (-1);
	if (setoldpwd(aenv) == -1)
	{
		free(cwd);
		return (-1);
	}
	if (addenv(aenv, cwd) == -1)
		puterror(strerror(errno));
	free(cwd);
	return (0);
}
