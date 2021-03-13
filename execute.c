/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 18:06:35 by user42            #+#    #+#             */
/*   Updated: 2021/03/13 16:02:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	setexitstatus(int csanity)
{
	if (csanity == NOCMD || csanity == NOFILE)
		g_var.g_exitstatus = EXIT_STAT_NOCMD;
	else if (csanity == NOEXEC || csanity == ISDIR)
		g_var.g_exitstatus = EXIT_STAT_NOEXEC;
	else
		g_var.g_exitstatus = EXIT_STAT_FAIL;
}

void
	execute(t_list *command, t_shell *shell)
{
	int		csanity;

	if (getcommandredir(command))
		if (redirect(command) == -1)
		{
			g_var.g_exitstatus = EXIT_STAT_FAIL;
			puterror(strerror(errno));
			return ;
		}
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
}

static void
	skipcommands(t_list **command, int ctype)
{
	while (getcommandtype(*command) >= ctype)
		*command = (*command)->next;
}

static void
	nlsignal(void)
{
	if (g_var.g_exitstatus == 128 + SIGINT
	|| g_var.g_exitstatus == 128 + SIGQUIT)
		write(STDERR, "\n", 1);
}

void
	cyclecommand(t_list *command, t_shell *shell)
{
	int	r;

	while (command && !shell->exit)
	{
		if (getcommandtype(command) == SIMPLE)
		{
			if ((r = expandcommand(command, shell->env)) < 0)
			{
				if (r == -1)
					puterror(strerror(errno));
			}
			else
				execute(command, shell);
		}
		else if (getcommandtype(command) == PIPE)
		{
			if (minipipe(command, shell) == -1)
				puterror(strerror(errno));
			skipcommands(&command, PIPE);
		}
		command = command->next;
		dup2(shell->stdincpy, STDIN);
		dup2(shell->stdoutcpy, STDOUT);
		nlsignal();
	}
}
