/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 11:17:08 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/01/12 15:17:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	openmode(int commandtype, char *filename)
{
	int		fd;

	fd = -1;
	if (commandtype == REDIRIN)
		fd = open(filename, O_RDONLY);
	else if (commandtype == REDIRTRUNC)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 000666);
	else if (commandtype == REDIRAPPEND)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 000666);
	return (fd);
}

static int
	skipfiles(t_list *command)
{
	int		fd;
	t_list	*current;

	current = command;
	while (getcommandtype(current) > REDIRECTION)
	{
		if ((fd = openmode(getcommandtype(current),
		getcmd(current->next))) == -1)
			return (-1);
		current = current->next;
		if (getcommandtype(current) < REDIRECTION)
			return (fd);
		else if (close(fd) < 0)
			return (-1);
	}
	return (-1);
}

static void
	exitstatredirfail(t_list *command, int cmdsanity)
{
	puterrorcmd(command, cmdsanity);
	if (cmdsanity == NOCMD)
		g_exitstatus = EXIT_STAT_NOCMD;
	else if (cmdsanity == NOEXEC || cmdsanity == ISDIR)
		g_exitstatus = EXIT_STAT_NOEXEC;
	else
		g_exitstatus = EXIT_STAT_FAIL;
}

int
	redirect(t_list *command, t_shell *shell)
{
	int		fd;
	int		cmdsanity;

	if ((cmdsanity = commandsanity(command, shell)) == -1)
		return (-1);
	if ((fd = skipfiles(command)) == -1)
		return (-1);
	if (!iserror(cmdsanity))
	{
		if (getcommandtype(command) == REDIRIN)
			dup2(fd, STDIN);
		else
			dup2(fd, STDOUT);
		execute(command, shell, cmdsanity);
	}
	else
		exitstatredirfail(command, cmdsanity);
	if (close(fd) < 0)
		return (-1);
	return (0);
}
