/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 13:07:04 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/21 16:00:10 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	cd(char **argv, t_list **aenv)
{
	t_list		*home;
	char		*wd;
	char		*addenvinput;
	int			r;

	if (!argv[0])
	{
		if (!(home = findenv(*aenv, "HOME")))
		{
			puterror(ERROR_NOHOME);
			return (1);
		}
		if ((r = chdir(getenvval(home))) == -1)
			return (-1);
	}
	else if ((r = chdir(argv[0])) == -1)
		return (-1);
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
	return (r);
}
