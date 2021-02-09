/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 14:35:01 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/01/11 16:45:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	exitshell(char **argv, t_list **aenv)
{
	int	i;

	(void)aenv;
	if (!argv[0])
		exit(g_exitstatus);
	i = 0;
	while (argv[0][i])
		if (!(ft_isdigit(argv[0][i++])))
		{
			puterror(ERROR_NAN);
			exit(1);
		}
	if (argv[1])
	{
		puterror(ERROR_TOO_MANY_ARG);
		return (-2);
	}
	exit(ft_atoi(argv[0]));
}
