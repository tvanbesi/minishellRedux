/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 14:05:34 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/14 17:20:40 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	puterrorcmd(t_list *command, int n)
{
	char	*cmd;

	cmd = getcmd(command);
	if (n == NOCMD)
	{
		write(STDERR, ERROR_NOCMD, ft_strlen(ERROR_NOCMD));
		write(STDERR, " : ", 3);
		write(STDERR, cmd, ft_strlen(cmd));
		write(STDERR, "\n", 1);
	}
	else if (n == NOEXEC)
	{
		write(STDERR, cmd, ft_strlen(cmd));
		write(STDERR, " : ", 3);
		write(STDERR, ERROR_ISNEXEC, ft_strlen(ERROR_ISNEXEC));
		write(STDERR, "\n", 1);
	}
	else if (n == ISDIR)
	{
		write(STDERR, cmd, ft_strlen(cmd));
		write(STDERR, " : ", 3);
		write(STDERR, ERROR_ISDIR, ft_strlen(ERROR_ISDIR));
		write(STDERR, "\n", 1);
	}
	else if (n == FATAL)
	{
		write(STDERR, ERROR_FATAL, ft_strlen(ERROR_FATAL));
		write(STDERR, "\n", 1);
	}
}

void
	puterror(char *msg)
{
	write(STDERR, msg, ft_strlen(msg));
	write(STDERR, "\n", 1);
}

void
	*error(char *msg)
{
	puterror(msg);
	return (NULL);
}
