/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 13:54:38 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/21 16:01:28 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	pwd(char **argv)
{
	char		*cwd;

	if (!(cwd = getcwd(NULL, 0)))
		return (-1);
	write(STDOUT, cwd, ft_strlen(cwd));
	free(cwd);
	write(STDOUT, "\n", 1);
	return (0);
}
