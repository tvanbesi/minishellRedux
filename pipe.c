/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 18:27:26 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/02/08 14:04:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	minipipechild(int pipeend, int fd[2], t_list *command, t_shell *shell)
{
	int		cmdsanity;
	int		commandtype;

	cmdsanity = commandsanity(command, shell);
	if (cmdsanity == -1)
		exit(FATAL);
	if (!iserror(cmdsanity) && !pipeend)
		dup2(fd[1], STDOUT);
	close(fd[0]);
	close(fd[1]);
	if (iserror(cmdsanity) && pipeend)
		puterrorcmd(command, cmdsanity);
	if (!iserror(cmdsanity))
		execute(command, shell, cmdsanity);
	else
		exit(cmdsanity);
	exit(g_exitstatus);
}

static void
	minipipeflowbytype(int commandtype, t_list *command, t_shell *shell)
{
	if (commandtype == PIPE)
	{
		if (minipipe(command->next, shell, 0) == -1)
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
		if (minipipe(command->next, shell, 1) == -1)
			puterror(strerror(errno));
	}
}

static int
	minipipeflow(int stat_loc, int fd[2], t_list *command, t_shell *shell)
{
	int		cmdsanity;
	int		commandtype;

	commandtype = getcommandtype(command->next);
	cmdsanity = commandsanity(command->next, shell);
	if (cmdsanity == -1)
		return (-1);
	if (!iserror(WEXITSTATUS(stat_loc))
		&& (!iserror(cmdsanity) && cmdsanity != EMPTY))
		dup2(fd[0], STDIN);
	close(fd[0]);
	close(fd[1]);
	minipipeflowbytype(commandtype, command, shell);
	if (iserror(WEXITSTATUS(stat_loc)))
		puterrorcmd(command, WEXITSTATUS(stat_loc));
	return (0);
}

static void
	exitstatpipeend(int stat_loc)
{
	if (WEXITSTATUS(stat_loc) == NOCMD)
		g_exitstatus = EXIT_STAT_NOCMD;
	else if (WEXITSTATUS(stat_loc) == NOEXEC || WEXITSTATUS(stat_loc) == ISDIR)
		g_exitstatus = EXIT_STAT_NOEXEC;
	else if (!iserror(WEXITSTATUS(stat_loc)))
		g_exitstatus = EXIT_STAT_SUCCESS;
	else
		g_exitstatus = EXIT_STAT_FAIL;
}

int
	minipipe(t_list *command, t_shell *shell, int pipeend)
{
	int		fd[2];
	int		stat_loc;

	if (pipe(fd) == -1)
		return (-1);
	g_pid = fork();
	if (g_pid == -1)
		return (-1);
	if (g_pid == 0)
		minipipechild(pipeend, fd, command, shell);
	else
	{
		if (waitpid(g_pid, &stat_loc, 0) != g_pid)
			return (-1);
		if (WIFEXITED(stat_loc) && !pipeend)
		{
			if (minipipeflow(stat_loc, fd, command, shell) == -1)
				return (-1);
		}
		else if (WIFEXITED(stat_loc) && pipeend)
			exitstatpipeend(stat_loc);
	}
	return (0);
}
