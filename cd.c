/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 13:07:04 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/16 17:54:25 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	cd(char **argv, t_list **aenv)
{
	char		*pwd;
	t_list		*home;

	if (!argv[0])
	{
		if (!(home = findenv(*aenv, "HOME")))
			return (0);
		if (!(pwd = getcwd(NULL, 0)))
			return (-1);
		if (!(pwd = ft_strjoin("PATH=", pwd)))
			return (-1);
		//This will leak, need fixing
		if (addenv(aenv, pwd) == -1)
			return (-1);
		return (chdir(getenvval(home)));
	}
	if (argv[1])
	{
		puterror(ERROR_TOO_MANY_ARG);
		return (-2);
	}
	return (chdir(argv[0]));
}
