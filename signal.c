/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 16:08:27 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/02/09 16:10:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	sigint(int n)
{
	(void)n;
	if (g_pid == 0)
		exit(BREAK);
	else
		kill(g_pid, SIGINT);
}

void
	sigquit(int n)
{
	(void)n;
	if (g_pid == 0)
		write(STDOUT, "\b \b", 3);
	else
		kill(g_pid, SIGQUIT);
}
