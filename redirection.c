/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 11:17:08 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/01 16:12:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	openmode(int mode, char *filename)
{
	int		fd;

	fd = -1;
	if (mode == REDIRIN)
		fd = open(filename, O_RDONLY);
	else if (mode == REDIRTRUNC)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 000666);
	else if (mode == REDIRAPPEND)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 000666);
	return (fd);
}

static int
	skipfiles(t_list *command)
{
	int			fd;
	t_command	*commandcontent;
	t_list		*current;

	commandcontent = command->content;
	current = commandcontent->redirections;
	while (current)
	{
		if ((fd = openmode(getredirtype(current), getredirstr(current))) == -1)
			return (-1);
		current = current->next;
		if (current)
			close(fd);
	}
	return (fd);
}

int
	redirect(t_list *command, t_shell *shell)
{
	int			fd;
	t_command	*commandcontent;

	if ((fd = skipfiles(command)) == -1)
		return (-1);
	commandcontent = command->content;
	if (getredirtype(ft_lstlast(commandcontent->redirections)) == REDIRIN)
		dup2(fd, STDIN);
	else
		dup2(fd, STDOUT);
	close(fd);
	return (0);
}
