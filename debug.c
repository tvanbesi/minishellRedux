/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 02:16:17 by user42            #+#    #+#             */
/*   Updated: 2021/03/08 22:43:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	showtoken(void *p)
{
	t_token	*content;

	content = p;
	printf("%d\t|%s|\n", content->type, content->s);
}

void
	showcommand(void *p)
{
	t_command	*content;
	t_list		*argv;
	t_list		*current;
	t_token		*token;

	content = p;
	argv = content->argv;
	if (!argv)
	{
		printf("no command\n");
		return ;
	}
	if (content->type == SIMPLE)
		printf("SIMPLE ");
	else if (content->type == PIPE)
		printf("PIPE ");
	printf("COMMAND\n");
	while (argv)
	{
		showtoken(argv->content);
		argv = argv->next;
	}
	current = content->redirections;
	while (current)
	{
		token = getredirtoken(current);
		printf("%d\t%s\n", getredirtype(current), token->s);
		current = current->next;
	}
	printf("\n\n");
}
