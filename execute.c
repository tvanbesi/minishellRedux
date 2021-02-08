/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 12:41:35 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/02/08 11:59:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	execute(t_list *command, t_shell *shell, int n)
{
	char	*cmd;

	cmd = getcmd(command);
	if (!cmd)
	{
		g_exitstatus = EXIT_STAT_SUCCESS;
		return ;
	}
	if (n == EXEC)
	{
		if (process(cmd, command, shell) == -1)
			puterror(strerror(errno));
	}
	else if (isbuiltin(n))
		builtin(command, shell, n);
	dup2(shell->stdincpy, STDIN);
	dup2(shell->stdoutcpy, STDOUT);
}

static void
	executesimple(t_list *command, t_shell *shell)
{
	int		cmdsanity;

	cmdsanity = commandsanity(command, shell);
	if (cmdsanity == -1)
		puterror(strerror(errno));
	else if (!iserror(cmdsanity))
		execute(command, shell, cmdsanity);
	else
	{
		puterrorcmd(command, cmdsanity);
		if (cmdsanity == NOCMD)
			g_exitstatus = EXIT_STAT_NOCMD;
		else if (cmdsanity == NOEXEC || cmdsanity == ISDIR)
			g_exitstatus = EXIT_STAT_NOEXEC;
		else
			g_exitstatus = EXIT_STAT_FAIL;
	}
}

static void
	executeredir(t_list *command, t_shell *shell)
{
	if (redirect(command, shell) == -1)
	{
		puterror(strerror(errno));
		g_exitstatus = EXIT_STAT_FAIL;
	}
}

void
	cyclecommand(t_list *command, t_shell *shell)
{
	int		commandtype;

	while (command)
	{
		commandtype = getcommandtype(command);
		if (commandtype == SIMPLE)
			executesimple(command, shell);
		else if (commandtype == PIPE)
		{
			if (minipipe(command, shell, 0) == -1)
				puterror(strerror(errno));
			while (getcommandtype(command) >= PIPE)
				command = command->next;
			dup2(shell->stdincpy, STDIN);
			dup2(shell->stdoutcpy, STDOUT);
		}
		else if (commandtype > REDIRECTION)
		{
			executeredir(command, shell);
			while (getcommandtype(command) > REDIRECTION)
				command = command->next;
		}
		command = command->next;
	}
}
