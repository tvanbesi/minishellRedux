/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 13:07:04 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/13 18:24:15 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	cd(char **argv)
{
	char		*path;

	if (!argv[0])
		return (chdir(""));	//cd to HOME
	if (argv[1])
	{
		puterror(ERROR_TOO_MANY_ARG);
		return (-2);
	}
	path = argv[0];
	return (chdir(path));
}
