/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 18:06:35 by user42            #+#    #+#             */
/*   Updated: 2021/02/13 14:35:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	setexitstatus(int csanity)
{
	if (csanity == NOCMD || csanity == NOFILE)
		g_exitstatus = EXIT_STAT_NOCMD;
	else if (csanity == NOEXEC || csanity == ISDIR)
		g_exitstatus = EXIT_STAT_NOEXEC;
	else
		g_exitstatus = EXIT_STAT_FAIL;
}

void
	execute(t_list *command, t_shell *shell)
{
	int		csanity;

	if (expand(command, shell->env) == -1)
		puterror(strerror(errno));
	csanity = commandsanity(command, shell);
	if (isbuiltin(csanity))
		builtin(command, shell);
	else if (csanity == EXEC)
		process(command, shell);
	else if (iserror(csanity))
	{
		puterrorcmd(getcmd(command), csanity);
		setexitstatus(csanity);
	}
	dup2(shell->stdincpy, STDIN);
	dup2(shell->stdoutcpy, STDOUT);
}

void
	cyclecommand(t_list *command, t_shell *shell)
{
	int		ctype;

	while (command)
	{
		ctype = getcommandtype(command);
		if (ctype == SIMPLE)
			execute(command, shell);
		else if (ctype == PIPE)
		{
			if (minipipe(command, shell) == -1)
				puterror(strerror(errno));
			while (getcommandtype(command) >= PIPE)
				command = command->next;
		}
		else if (ctype > REDIRECTION)
		{
			if (redirect(command, shell) == -1)
				puterror(strerror(errno));
			execute(command, shell);
			while (getcommandtype(command) > REDIRECTION)
				command = command->next;
		}
		command = command->next;
	}
}
