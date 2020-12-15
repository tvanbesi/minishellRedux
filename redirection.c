/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 11:17:08 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/15 12:11:22 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	redirect(t_list *command, t_shell *shell)
{
	int		file;

	if ((file = open(getcmd(command->next), O_WRONLY | O_CREAT | O_TRUNC, 0777)) < 0)
		return (-1);
	dup2(file, STDOUT);
	execute(command, shell);
	close(file);
	return (0);
}
