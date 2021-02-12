/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:29:47 by user42            #+#    #+#             */
/*   Updated: 2021/02/12 18:58:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	builtin(t_list *command, t_shell *shell)
{
	char	**argv;
	int		n;
	int		r;

	argv = getcommandargv(command);
	n = commandsanity(command, shell);
	n -= BUILTIN_START + 1;
	if ((r = (*(shell->b)[n])(argv, &shell->env)) == -1)
		puterror(strerror(errno));
	g_exitstatus = r == 0 ? EXIT_STAT_SUCCESS : EXIT_STAT_FAIL;
}
