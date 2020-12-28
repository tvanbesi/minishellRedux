/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 12:41:35 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/22 09:20:05 by tvanbesi         ###   ########.fr       */
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

void
	cyclecommand(t_list *command, t_shell *shell)
{
	t_list	*current;
	int		commandtype;
	int		cmdsanity;

	if (!command)
		return ;
	current = command;
	while (current)
	{
		commandtype = getcommandtype(current);
		if (commandtype == SIMPLE)
		{
			if ((cmdsanity = commandsanity(current, shell)) == -1)
				puterror(strerror(errno));
			else if (!iserror(cmdsanity))
				execute(current, shell, cmdsanity);
			else
			{
				puterrorcmd(current, cmdsanity);
				if (cmdsanity == NOCMD)
					g_exitstatus = EXIT_STAT_NOCMD;
				else if (cmdsanity == NOEXEC || cmdsanity == ISDIR)
					g_exitstatus = EXIT_STAT_NOEXEC;
				else
					g_exitstatus = EXIT_STAT_FAIL;
			}
		}
		else if (commandtype == PIPE)
		{
			if (minipipe(current, shell, 0) == -1)
				puterror(strerror(errno));
			while (getcommandtype(current) >= PIPE)
				current = current->next;
			dup2(shell->stdincpy, STDIN);
			dup2(shell->stdoutcpy, STDOUT);
		}
		else if (commandtype > REDIRECTION)
		{
			if (redirect(current, shell) == -1)
			{
				puterror(strerror(errno));
				g_exitstatus = EXIT_STAT_FAIL;
			}
			while (getcommandtype(current) > REDIRECTION)
				current = current->next;
		}
		current = current->next;
	}
}
