/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 14:35:01 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/17 09:09:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	exitnan(void)
{
	ft_putstr_fd("exit\n", STDERR);
	puterror(ERROR_NAN);
	exit(EXIT_STAT_ERRORPARSE);
}

static void
	argsanity(int s, char *p)
{
	if (s == 1)
	{
		if (ft_strncmp(p, "9223372036854775807", 20) > 0)
			exitnan();
	}
	else if (s == -1)
		if (ft_strncmp(p, "9223372036854775808", 20) > 0)
			exitnan();
}

static int
	toomanyarg(void)
{
	ft_putstr_fd("exit\n", STDERR);
	puterror(ERROR_TOO_MANY_ARG);
	return (-3);
}

static void
	exitandshowit(int n)
{
	ft_putstr_fd("exit\n", STDERR);
	exit(n);
}

int
	exitshell(t_list *argv, t_list **aenv)
{
	int		s;
	int		i;
	char	*arg;

	(void)aenv;
	if (!argv)
		exitandshowit(g_var.g_exitstatus);
	arg = gettokenstr(argv);
	i = 0;
	s = 1;
	if (arg[i] == '-' || arg[i] == '+')
		if (arg[i++] == '-')
			s = -1;
	argsanity(s, &arg[i]);
	if (!arg[0])
		exitnan();
	else
		while (arg[i])
			if (!(ft_isdigit(arg[i++])))
				exitnan();
	if (argv->next)
		return (toomanyarg());
	ft_putstr_fd("exit\n", STDERR);
	exit((unsigned)ft_atoi(arg));
}
