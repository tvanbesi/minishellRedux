/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 13:07:04 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/02/09 16:13:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	setpwdenv(t_list **aenv)
{
	char		*wd;
	char		*addenvinput;

	if (!(wd = getcwd(NULL, 0)))
		return (-1);
	if (!(addenvinput = ft_strjoin("PWD=", wd)))
	{
		free(wd);
		return (-1);
	}
	free(wd);
	if (addenv(aenv, addenvinput) == -1)
	{
		free(addenvinput);
		return (-1);
	}
	free(addenvinput);
	return (0);
}

int
	cd(char **argv, t_list **aenv)
{
	t_list		*home;

	if (!argv[0])
	{
		if (!(home = findenv(*aenv, "HOME")))
		{
			puterror(ERROR_NOHOME);
			return (-2);
		}
		if (chdir(getenvval(home)) == -1)
			return (-1);
	}
	else if (chdir(argv[0]) == -1)
		return (-1);
	if (setpwdenv(aenv) == -1)
		return (-1);
	return (0);
}
