/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 18:06:35 by user42            #+#    #+#             */
/*   Updated: 2021/02/13 15:48:41 by user42           ###   ########.fr       */
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

	if ((csanity = commandsanity(command, shell)) == -1)
	{
		puterror(strerror(errno));
		return ;
	}
	if (isbuiltin(csanity))
		builtin(command, shell, csanity);
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

static void
	skipcommands(t_list **command, int ctype)
{
	while (getcommandtype(*command) >= ctype)
		*command = (*command)->next;
}

void
	cyclecommand(t_list *command, t_shell *shell)
{
	while (command)
	{
		if (getcommandtype(command) == SIMPLE)
		{
			if (expand(command, shell->env) == -1)
				puterror(strerror(errno));
			execute(command, shell);
		}
		else if (getcommandtype(command) == PIPE)
		{
			if (minipipe(command, shell) == -1)
				puterror(strerror(errno));
			skipcommands(&command, PIPE);
		}
		else if (getcommandtype(command) > REDIRECTION)
		{
			if (redirect(command, shell) == -1)
				puterror(strerror(errno));
			else
				execute(command, shell);
			skipcommands(&command, REDIRECTION);
		}
		command = command->next;
	}
}
