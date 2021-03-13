/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 14:35:01 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/13 10:45:14 by user42           ###   ########.fr       */
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

static int
	toomanyarg(void)
{
	puterror(ERROR_TOO_MANY_ARG);
	return (-3);
}

int
	exitshell(t_list *argv, t_list **aenv)
{
	int		s;
	int		i;
	char	*arg;

	(void)aenv;
	if (!argv)
		exit(g_var.g_exitstatus);
	arg = gettokenstr(argv);
	i = 0;
	s = 1;
	if (arg[i] == '-' || arg[i] == '+')
		if (arg[i++] == '-')
			s = -1;
	argsanity(s, &arg[i]);
	while (arg[i])
		if (!(ft_isdigit(arg[i++])))
		{
			puterror(ERROR_NAN);
			exit(EXIT_STAT_ERRORPARSE);
		}
	if (argv->next)
		return (toomanyarg());
	exit((unsigned)ft_atoi(arg));
}
