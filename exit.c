/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 14:35:01 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/21 16:10:29 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	exitshell(char **argv)
{
	int	i;

	if (!argv[0])
		exit(g_exitstatus);
	i = 0;
	while (argv[0][i])
		if (!(ft_isdigit(argv[0][i++])))
		{
			puterror(ERROR_NAN);
			exit(1); //Compare with VM (255 on MacOS)
		}
	if (argv[1])
	{
		puterror(ERROR_TOO_MANY_ARG);
		return (1);
	}
	exit(ft_atoi(argv[0]));
}
