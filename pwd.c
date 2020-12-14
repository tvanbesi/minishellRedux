/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 13:54:38 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/13 18:25:10 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	pwd(char **argv)
{
	char		*cwd;

	if (argv[0])
	{
		puterror(ERROR_TOO_MANY_ARG);
		return (-2);
	}
	if (!(cwd = getcwd(NULL, 0)))
		return (-1);
	if (write(STDOUT, cwd, ft_strlen(cwd)) == -1)
	{
		free(cwd);
		return (-1);
	}
	free(cwd);
	if (write(STDOUT, "\n", 1) == -1)
		return (-1);
	return (0);
}
