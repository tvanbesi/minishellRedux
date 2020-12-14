/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 12:41:35 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/14 15:42:14 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	builtin(t_list *command, t_shell *shell)
{
	char	*cmd;
	char	**argv;

	cmd = getcmd(command);
	argv = getcommandargv(command);
	if (!ft_strncmp(cmd, "echo", 5))
		return (echo(argv));
	else if (!ft_strncmp(cmd, "cd", 3))
		return (cd(argv));
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (pwd(argv));
	else if (!ft_strncmp(cmd, "export", 7))
		return (export(argv, &shell->env));
	else if (!ft_strncmp(cmd, "unset", 6))
		return (unset(argv, &shell->env));
	else if (!ft_strncmp(cmd, "env", 4))
		return (env(argv, shell->env));
	else if (!ft_strncmp(cmd, "exit", 5))
		return (exitshell(argv));
	puterror(ERROR_CMD_NOT_FOUND);
	return (-2);
}

void
	execute(t_list *command, t_shell *shell)
{
	t_list	*current;
	char	*cmd;

	if (!command)
		return ;
	current = command;
	while (current)
	{
		cmd = getcmd(command);
		if (getcommandtype(current) == SIMPLE)
		{
			if (cmd[0] == '/')
				; //execve
			else if (builtin(command, shell) == -1)
				puterror(strerror(errno));
		}
		else
			printf("PIPE ET REDIRECTIONS PAS ENCORE FAIT DESO LES COCOS\n");
		current = current->next;
	}
}
