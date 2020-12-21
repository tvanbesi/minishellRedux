/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 16:08:27 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/21 13:28:11 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	sigint(int n)
{
	if (g_pid == 0)
		write(STDOUT, "\b\b  \n> ", 7);
	else
	{
		write(STDOUT, "\n", 1);
		g_exitstatus = 128 + SIGINT;
	}
	g_skipeof = 1;
}

void
	sigquit(int n)
{
	if (g_pid == 0)
		write(STDOUT, "\b\b  \b\b", 6);
	else
	{
		write(STDOUT, "Quit: 3\n", 8);
		g_exitstatus = 128 + SIGQUIT;
	}
	g_skipeof = 1;
}
