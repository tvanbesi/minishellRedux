/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 18:27:26 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/22 09:26:27 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	minipipe(t_list *command, t_shell *shell)
{
	int		fd[2];
	int		stat_loc;
	int		cmdsanity;
	int		commandtype;

	if (pipe(fd) == -1)
		return (-1);
	if ((g_pid = fork()) == -1)
		return (-1);
	if (g_pid == 0)
	{
		if ((cmdsanity = commandsanity(command, shell)) == -1)
			exit(FATAL);
		if (!iserror(cmdsanity))
			dup2(fd[1], STDOUT);
		close(fd[0]);
		close(fd[1]);
		if (!iserror(cmdsanity))
			execute(command, shell, cmdsanity);
		else
			exit(cmdsanity);
		exit(g_exitstatus);
	}
	else
	{
		if (waitpid(g_pid, &stat_loc, 0) != g_pid)
			return (-1);
		if (WIFEXITED(stat_loc))
		{
			commandtype = getcommandtype(command->next);
			if ((cmdsanity = commandsanity(command->next, shell)) == -1)
				return (-1);
			if (!iserror(WEXITSTATUS(stat_loc)) && (!iserror(cmdsanity) && cmdsanity != EMPTY))
				dup2(fd[0], STDIN);
			close(fd[0]);
			close(fd[1]);
			if (commandtype == PIPE)
			{
				if (minipipe(command->next, shell) == -1)
					puterror(strerror(errno));
			}
			else if (commandtype > REDIRECTION)
			{
				if (redirect(command->next, shell) == -1)
				{
					puterror(strerror(errno));
					g_exitstatus = EXIT_STAT_FAIL;
				}
			}
			else if (commandtype == SIMPLE)
			{
				if (!iserror(cmdsanity))
					execute(command->next, shell, cmdsanity);
				else
				{
					puterrorcmd(command->next, cmdsanity);
					if (cmdsanity == NOCMD)
						g_exitstatus = EXIT_STAT_NOCMD;
					else if (cmdsanity == NOEXEC || cmdsanity == ISDIR)
						g_exitstatus = EXIT_STAT_NOEXEC;
					else
						g_exitstatus = EXIT_STAT_FAIL;
				}
			}
			if (iserror(WEXITSTATUS(stat_loc)))
				puterrorcmd(command, WEXITSTATUS(stat_loc));
		}
		else if (WIFSIGNALED(stat_loc))
			printf("Signal received in pipe\n");
	}
	return (0);
}
