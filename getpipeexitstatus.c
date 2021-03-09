/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpipeexitstatus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 21:41:27 by user42            #+#    #+#             */
/*   Updated: 2021/03/09 22:54:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	getpipeexitstatus(int nchildren, int *pid_children)
{
	int	stat_loc;
	int	r;
	int	i;

	i = 0;
	r = 0;
	while (nchildren - i > 0)
	{
		if (waitpid(pid_children[i], &stat_loc, 0) == -1)
			return (-1);
		if (i == nchildren - 1)
			r = stat_loc;
		i++;
	}
	if (WIFEXITED(r))
		return (WEXITSTATUS(r));
	else if (WIFSIGNALED(r))
		return (WTERMSIG(r));
	else
		return (0);
}
