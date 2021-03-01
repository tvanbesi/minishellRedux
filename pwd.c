/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 13:54:38 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/02/28 15:58:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	pwd(char **argv, t_list **aenv)
{
	char		*cwd;

	(void)aenv;
	(void)argv;
	if (!(cwd = getcwd(NULL, 0)))
	{
		puterror(strerror(errno));
		if (!(cwd = ft_strdup(getenvval(findenv(*aenv, "PWD")))))
			return (-1);
	}
	write(STDOUT, cwd, ft_strlen(cwd));
	free(cwd);
	write(STDOUT, "\n", 1);
	return (0);
}
