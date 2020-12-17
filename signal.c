/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 16:08:27 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/17 14:30:51 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	sigint(int n)
{
	write(STDOUT, "\b\b  \n> ", 7);
	g_skipeof = 1;
}

void
	sigquit(int n)
{
	write(STDOUT, "\b\b  \b\b", 6);
	g_skipeof = 1;
}
