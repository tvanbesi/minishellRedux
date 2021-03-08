/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorcmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:37:25 by user42            #+#    #+#             */
/*   Updated: 2021/03/08 19:40:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	errornocmd(char *cmd)
{
	char	msg[1000];
	int		n;

	ft_strlcpy(msg, ERROR_NOCMD, BUFFER_SIZE_ERRORMSG);
	ft_strlcat(msg, " : ", BUFFER_SIZE_ERRORMSG);
	ft_strlcat(msg, cmd, BUFFER_SIZE_ERRORMSG);
	n = ft_strlcat(msg, "\n", BUFFER_SIZE_ERRORMSG);
	write(STDERR, msg, n);
}

static void
	errornoexec(char *cmd)
{
	char	msg[1000];
	int		n;

	ft_strlcpy(msg, cmd, BUFFER_SIZE_ERRORMSG);
	ft_strlcat(msg, " : ", BUFFER_SIZE_ERRORMSG);
	ft_strlcat(msg, ERROR_ISNEXEC, BUFFER_SIZE_ERRORMSG);
	n = ft_strlcat(msg, "\n", BUFFER_SIZE_ERRORMSG);
	write(STDERR, msg, n);
}

static void
	errornofile(char *cmd)
{
	char	msg[1000];
	int		n;

	ft_strlcpy(msg, cmd, BUFFER_SIZE_ERRORMSG);
	ft_strlcat(msg, " : ", BUFFER_SIZE_ERRORMSG);
	ft_strlcat(msg, ERROR_NOFILE, BUFFER_SIZE_ERRORMSG);
	n = ft_strlcat(msg, "\n", BUFFER_SIZE_ERRORMSG);
	write(STDERR, msg, n);
}

static void
	errorisdir(char *cmd)
{
	char	msg[1000];
	int		n;

	ft_strlcpy(msg, cmd, BUFFER_SIZE_ERRORMSG);
	ft_strlcat(msg, " : ", BUFFER_SIZE_ERRORMSG);
	ft_strlcat(msg, ERROR_ISDIR, BUFFER_SIZE_ERRORMSG);
	n = ft_strlcat(msg, "\n", BUFFER_SIZE_ERRORMSG);
	write(STDERR, msg, n);
}

void
	puterrorcmd(char *cmd, int n)
{
	if (n == NOCMD)
		errornocmd(cmd);
	else if (n == NOEXEC)
		errornoexec(cmd);
	else if (n == ISDIR)
		errorisdir(cmd);
	else if (n == NOFILE)
		errornofile(cmd);
}
