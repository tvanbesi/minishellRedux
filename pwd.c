/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 13:54:38 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/11 19:27:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	pwd(t_list *argv, t_list **aenv)
{
	char		*cwd;
	char		*tmp;
	int			doubleslash;

	(void)argv;
	doubleslash = 0;
	if ((tmp = getenvvalbyname(*aenv, "PWD")))
		if (tmp[0] == '/' && tmp[1] == '/')
			doubleslash = 1;
	if (!(cwd = getcwd(NULL, 0)))
	{
		if (!tmp)
			return (-1);
		else if (!(cwd = ft_strdup(tmp)))
			return (-1);
	}
	if (doubleslash)
		write(STDOUT, "/", 1);
	write(STDOUT, cwd, ft_strlen(cwd));
	free(cwd);
	write(STDOUT, "\n", 1);
	return (0);
}
