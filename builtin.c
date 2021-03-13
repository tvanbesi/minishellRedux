/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:29:47 by user42            #+#    #+#             */
/*   Updated: 2021/03/13 10:44:59 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	builtin(t_list *command, t_shell *shell, int csanity)
{
	t_list	*argv;
	int		r;

	argv = getcommandargv(command);
	argv = argv->next;
	if (csanity == EXITSHELL)
		shell->exit = 1;
	csanity -= BUILTIN_START + 1;
	if ((r = (*(shell->b)[csanity])(argv, &shell->env)) == -1)
		puterror(strerror(errno));
	if (r == 0)
		g_var.g_exitstatus = EXIT_STAT_SUCCESS;
	else if (r == -1 || r == -3)
		g_var.g_exitstatus = EXIT_STAT_FAIL;
	else if (r == -2)
		g_var.g_exitstatus = EXIT_STAT_ERRORPARSE;
}
