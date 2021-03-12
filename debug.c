/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 12:16:00 by user42            #+#    #+#             */
/*   Updated: 2021/03/12 18:15:03 by user42           ###   ########.fr       */
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

static void
	showredir(t_list *redir)
{
	while (redir)
	{
		if (getredirtype(redir) == REDIRIN)
			printf("<\t");
		if (getredirtype(redir) == REDIRAPPEND)
			printf(">>\t");
		if (getredirtype(redir) == REDIRTRUNC)
			printf(">\t");
		printf("REDIR\t%s\n", getredirstr(redir));
		redir = redir->next;
	}
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
	showredir(commandcontent->redirections);
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
