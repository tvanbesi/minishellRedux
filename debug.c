/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 12:16:00 by user42            #+#    #+#             */
/*   Updated: 2021/03/10 17:24:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	showtoken(void *p)
{
	t_token	*content;

	content = p;
	printf("|%s|\n", content->s);
}

void
	showcommand(void *p)
{
	t_list		*current;
	t_command	*commandcontent;

	commandcontent = p;
	if (commandcontent->type == SIMPLE)
		printf("SIMPLE\n");
	else if (commandcontent->type == PIPE)
		printf("PIPE\n");
	else
		printf("BAD CMD TYPE\n");
	current = commandcontent->redirections;
	while (current)
	{
		if (getredirtype(current) == REDIRIN)
			printf("<\t");
		if (getredirtype(current) == REDIRAPPEND)
			printf(">>\t");
		if (getredirtype(current) == REDIRTRUNC)
			printf(">\t");
		printf("REDIR\t%s\n", getredirstr(current));
		current = current->next;
	}
	current = commandcontent->argv;
	if (!current)
		printf("NOARGV\n");
	while (current)
	{
		printf("|%s|\t", gettokenstr(current));
		current = current->next;
	}
	printf("\n");
}
