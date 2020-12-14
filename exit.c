/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 14:35:01 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/13 18:26:53 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	exitshell(char **argv)
{
	if (!argv[0])
		exit(0);	//Parameter should be exit status of last command
	if (argv[1])
	{
		puterror(ERROR_TOO_MANY_ARG);
		return (-2);
	}
	exit(ft_atoi(argv[0]));
}
