/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 18:27:26 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/18 08:52:47 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	minipipe(t_list *command, t_shell *shell)
{
	int		fd[2];
	int		stat_loc;

	if (pipe(fd) == -1)
		return (-1);
	if ((g_pid = fork()) == -1)
		return (-1);	//Maybe the fd should be closed if fork fail ? Try
	if (g_pid == 0)
	{
		dup2(fd[1], STDOUT);
		close(fd[0]);
		close(fd[1]);
		execute(command, shell);
		exit(0);	//Should return correct exit status
	}
	else
	{
		if (waitpid(g_pid, &stat_loc, 0) != g_pid)
			return (-1);
		dup2(fd[0], STDIN);
		close(fd[1]);
		close(fd[0]);
		if (getcommandtype(command->next) == PIPE)
		{
			command = command->next;
			if (minipipe(command, shell) == -1)
				return (-1);
		}
		if (getcommandtype(command->next) > REDIRECTION)
			redirect(command->next, shell);
		else
			execute(command->next, shell);
	}
	return (0);
}
