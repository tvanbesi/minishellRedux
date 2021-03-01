/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 14:35:01 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/01 00:25:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	argsanity(int s, char *p)
{
	if (s == 1)
	{
		if (ft_strncmp(p, "9223372036854775807", 20) > 0)
		{
			puterror(ERROR_NAN);
			exit(2);
		}
	}
	else if (s == -1)
		if (ft_strncmp(p, "9223372036854775808", 20) > 0)
		{
			puterror(ERROR_NAN);
			exit(2);
		}
}

int
	exitshell(char **argv, t_list **aenv)
{
	int	i;
	int	s;

	(void)aenv;
	if (!argv[0])
		exit(g_exitstatus);
	i = 0;
	s = 1;
	if (argv[0][i] == '-' || argv[0][i] == '+')
	{
		if (argv[0][i] == '-')
			s = -1;
		i++;
	}
	argsanity(s, &argv[0][i]);
	while (argv[0][i])
		if (!(ft_isdigit(argv[0][i++])))
		{
			puterror(ERROR_NAN);
			exit(2);
		}
	if (argv[1])
	{
		puterror(ERROR_TOO_MANY_ARG);
		return (-2);
	}
	exit((unsigned)ft_atoi(argv[0]));
}
