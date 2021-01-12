/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wait.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:27:41 by user42            #+#    #+#             */
/*   Updated: 2021/01/11 19:27:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	setexitstatus(int stat_loc)
{
	if (WIFEXITED(stat_loc))
		g_exitstatus = WEXITSTATUS(stat_loc);
	else if (WIFSIGNALED(stat_loc))
		g_exitstatus = 128 + WTERMSIG(stat_loc);
}
