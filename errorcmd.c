/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorcmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:37:25 by user42            #+#    #+#             */
/*   Updated: 2021/02/12 18:57:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	errornocmd(char *cmd)
{
	write(STDERR, ERROR_NOCMD, ft_strlen(ERROR_NOCMD));
	write(STDERR, " : ", 3);
	write(STDERR, cmd, ft_strlen(cmd));
	write(STDERR, "\n", 1);
}

static void
	errornoexec(char *cmd)
{
	write(STDERR, cmd, ft_strlen(cmd));
	write(STDERR, " : ", 3);
	write(STDERR, ERROR_ISNEXEC, ft_strlen(ERROR_ISNEXEC));
	write(STDERR, "\n", 1);
}

static void
	errorisdir(char *cmd)
{
	write(STDERR, cmd, ft_strlen(cmd));
	write(STDERR, " : ", 3);
	write(STDERR, ERROR_ISDIR, ft_strlen(ERROR_ISDIR));
	write(STDERR, "\n", 1);
}

void
	puterrorcmd(t_list *command, t_shell *shell)
{
	int		n;
	char	*cmd;

	cmd = getcmd(command);
	n = commandsanity(command, shell);
	if (n == NOCMD)
		errornocmd(cmd);
	else if (n == NOEXEC)
		errornoexec(cmd);
	else if (n == ISDIR)
		errorisdir(cmd);
}
