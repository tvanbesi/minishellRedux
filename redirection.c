/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 11:17:08 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/08 18:14:59 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	openmode(int fd[2], int mode, char *fname)
{
	if (mode == REDIRIN)
		return ((fd[0] = open(fname, O_RDONLY)));
	else if (mode == REDIRTRUNC)
		return ((fd[1] = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 000666)));
	else if (mode == REDIRAPPEND)
		return ((fd[1] = open(fname, O_WRONLY | O_CREAT | O_APPEND, 000666)));
	return (-1);
}

static int
	skipfiles(int fd[2], t_list *command)
{
	t_list		*current;

	current = getcommandredir(command);
	while (current)
	{
		if (openmode(fd, getredirtype(current), getredirstr(current)) == -1)
			return (-1);
		current = current->next;
		if (current)
		{
			if (getredirtype(current) == REDIRIN)
				close(fd[0]);
			else
				close(fd[1]);
		}
	}
	return (0);
}

int
	redirect(t_list *command)
{
	int			fd[2];

	fd[0] = -1;
	fd[1] = -1;
	if (skipfiles(fd, command) == -1)
		return (-1);
	if (fd[0] != -1)
	{
		dup2(fd[0], STDIN);
		close(fd[0]);
	}
	if (fd[1] != -1)
	{
		dup2(fd[1], STDOUT);
		close(fd[1]);
	}
	return (0);
}
