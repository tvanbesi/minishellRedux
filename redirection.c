/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 11:17:08 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/16 13:55:24 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	openmode(int commandtype, char *filename)
{
	int		fd;

	if (commandtype == REDIRIN
	&& (fd = open(filename, O_RDONLY) < 0))
		return (-1);
	if (commandtype == REDIRTRUNC
	&& (fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 000666)) < 0)
		return (-1);
	if (commandtype == REDIRAPPEND
	&& (fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 000666)) < 0)
		return (-1);
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
		if ((fd = openmode(getcommandtype(current), getcmd(current->next))) == -1)
			return (-1);
		current = current->next;
		if (getcommandtype(current) < REDIRECTION)
			return (fd);
		else if (close(fd) < 0)
			return (-1);
	}
	return (-1);
}

int
	redirect(t_list *command, t_shell *shell)
{
	int		fd;

	if ((fd = skipfiles(command)) == -1)
		return (-1);
	if (getcommandtype(command) == REDIRIN)
		dup2(fd, STDIN);
	else
		dup2(fd, STDOUT);
	execute(command, shell);
	if (close(fd) < 0)
		return (-1);
	return (0);
}
