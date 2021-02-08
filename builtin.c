/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:29:47 by user42            #+#    #+#             */
/*   Updated: 2021/02/08 11:45:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	builtin(t_list *command, t_shell *shell, int n)
{
	char	**argv;
	int		r;

	argv = getcommandargv(command);
	n -= BUILTIN_START + 1;
	r = (*(shell->b)[n])(argv, &shell->env);
	if (r == -1)
		puterror(strerror(errno));
	if (r)
		g_exitstatus = EXIT_STAT_FAIL;
	else
		g_exitstatus = EXIT_STAT_SUCCESS;
}
