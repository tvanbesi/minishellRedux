/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:29:47 by user42            #+#    #+#             */
/*   Updated: 2021/03/02 03:32:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	builtin(t_list *command, t_shell *shell, int csanity)
{
	char	**argv;
	int		r;

	argv = getcommandargv(command);
	if (csanity == EXITSHELL)
		shell->exit = 1;
	csanity -= BUILTIN_START + 1;
	if ((r = (*(shell->b)[csanity])(argv, &shell->env)) == -1 && errno != 0)
		puterror(strerror(errno));
	if (r == 0)
		g_exitstatus = EXIT_STAT_SUCCESS;
	else if (r == -1)
		g_exitstatus = EXIT_STAT_FAIL;
	else if (r == -2)
		g_exitstatus = EXIT_STAT_ERRORPARSE;
}
