/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 13:54:38 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/11 01:17:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	pwd(t_list *argv, t_list **aenv)
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
		return (-1);
	write(STDOUT, cwd, ft_strlen(cwd));
	free(cwd);
	write(STDOUT, "\n", 1);
	return (0);
}
