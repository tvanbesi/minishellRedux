/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorcmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:37:25 by user42            #+#    #+#             */
/*   Updated: 2021/02/27 14:27:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	errornocmd(char *cmd)
{
	printf("%s : %s\n", ERROR_NOCMD, cmd);
}

static void
	errornoexec(char *cmd)
{
	printf("%s : %s\n", cmd, ERROR_ISNEXEC);
}

static void
	errornofile(char *cmd)
{
	printf("%s : %s\n", cmd, ERROR_NOFILE);
}

static void
	errorisdir(char *cmd)
{
	printf("%s : %s\n", cmd, ERROR_ISDIR);
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
