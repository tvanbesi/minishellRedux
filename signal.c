/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 16:08:27 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/09 04:07:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	sigint(int n)
{
	(void)n;
	if (g_pid == 0)
	{
		write(STDERR, "\n> ", 3);
		g_exitstatus = 128 + SIGINT;
	}
	else
		kill(g_pid, SIGINT);
}

void
	sigquit(int n)
{
	(void)n;
	if (g_pid == 0)
	{
		write(STDERR, "\b\b  \b\b", 6);
		g_exitstatus = 128 + SIGQUIT;
	}
	else
		kill(g_pid, SIGQUIT);
}
