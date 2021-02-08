/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 16:08:27 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/02/08 15:26:44 by user42           ###   ########.fr       */
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
