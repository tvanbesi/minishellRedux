/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 11:17:08 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/16 06:57:33 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	redirect(t_list *command, t_shell *shell)
{
	int		file;

	if (getcommandtype(command) == REDIRTRUNC)
	{
		if ((file = open(getcmd(command->next), O_WRONLY | O_CREAT | O_TRUNC, 000666)) < 0)
			return (-1);
		dup2(file, STDOUT);
		execute(command, shell);
	}
	else if (getcommandtype(command) == REDIRAPPEND)
	{
		if ((file = open(getcmd(command->next), O_WRONLY | O_CREAT | O_APPEND, 000666)) < 0)
			return (-1);
		dup2(file, STDOUT);
		execute(command, shell);
	}
	else if (getcommandtype(command) == REDIRIN)
	{
		if ((file = open(getcmd(command->next), O_RDONLY)))
			return (-1);
		dup2(file, STDIN);
		execute(command, shell);
	}
	close(file);
	return (0);
}
