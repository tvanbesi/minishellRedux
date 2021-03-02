/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 13:54:38 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/02 02:35:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	pwd(char **argv, t_list **aenv)
{
	char		*cwd;
	t_list		*env;

	(void)aenv;
	(void)argv;
	if ((env = findenv(*aenv, "PWD")))
	{
		if (!(cwd = ft_strdup(getenvval(env))))
			return (-1);
	}
	else if (!(cwd = getcwd(NULL, 0)))
	{
		puterror(strerror(errno));
		return (-1);
	}
	write(STDOUT, cwd, ft_strlen(cwd));
	free(cwd);
	write(STDOUT, "\n", 1);
	return (0);
}
