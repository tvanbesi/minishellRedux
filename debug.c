/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 12:16:00 by user42            #+#    #+#             */
/*   Updated: 2021/03/10 12:28:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	showcommand(void *p)
{
	t_list		*current;
	t_command	*commandcontent;

	commandcontent = p;
	current = commandcontent->redirections;
	while (current)
	{
		printf("REDIR\t%s\n", getredirstr(current));
		current = current->next;
	}
	current = commandcontent->argv;
	while (current)
	{
		printf("|%s|\t", gettokenstr(current));
		current = current->next;
	}
	printf("\n");
}
