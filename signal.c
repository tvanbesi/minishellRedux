/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 16:08:27 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/13 10:45:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	sigint(int n)
{
	(void)n;
	g_var.g_exitstatus = 128 + SIGINT;
	if (g_var.g_pid == 0)
		write(STDERR, "\n> ", 3);
}

void
	sigquit(int n)
{
	(void)n;
	g_var.g_exitstatus = 128 + SIGQUIT;
	if (g_var.g_pid == 0)
		write(STDERR, "\b\b  \b\b", 6);
}
