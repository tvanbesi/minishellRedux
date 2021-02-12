/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 18:06:35 by user42            #+#    #+#             */
/*   Updated: 2021/02/12 19:33:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	execute(t_list *command, t_shell *shell)
{
	int		csanity;

	csanity = commandsanity(command, shell);
	if (isbuiltin(csanity))
		builtin(command, shell);
	else if (csanity == EXEC)
		process(command, shell);
	else if (iserror(csanity))
		puterrorcmd(command, shell);
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
