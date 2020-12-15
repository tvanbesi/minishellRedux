/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 18:27:26 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/15 10:39:16 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	minipipe(t_list *command, t_shell *shell)
{
	int		fd[2];
	pid_t	pid;
	int		stat_loc;

	if (pipe(fd) == -1)
		return (-1);
	if ((pid = fork()) == -1)
		return (-1);	//Maybe the fd should be closed if fork fail ? Try
	if (pid == 0)
	{
		dup2(fd[1], STDOUT);
		close(fd[0]);
		close(fd[1]);
		execute(command, shell);
		exit(0);	//Should return correct exit status
	}
	else
	{
		if (waitpid(pid, &stat_loc, 0) != pid)
			return (-1);
		dup2(fd[0], STDIN);
		close(fd[1]);
		close(fd[0]);
		if (getcommandtype(command->next) == PIPE)
		{
			command = command->next;
			minipipe(command, shell);
		}
		execute(command->next, shell);
	}
	return (0);
}
