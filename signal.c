/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 16:08:27 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/22 11:23:55 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	sigint(int n)
{
	if (g_pid == 0)
		exit(BREAK);
	else
		kill(g_pid, SIGINT);
}

void
	sigquit(int n)
{
	if (g_pid == 0)
		write(STDOUT, "\b \b", 3);
	else
		kill(g_pid, SIGQUIT);
}
