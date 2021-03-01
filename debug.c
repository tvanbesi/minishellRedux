/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 02:16:17 by user42            #+#    #+#             */
/*   Updated: 2021/03/01 10:11:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	showtoken(void *p)
{
	t_token	*content;

	content = p;
	printf("%d\t%s\n", content->type, content->s);
}

void
	showcommand(void *p)
{
	t_command	*content;
	char		**argv;
	t_list		*current;

	content = p;
	printf("COMMAND\n%d\t%s\n", content->type, content->cmd);
	argv = content->argv;
	if (argv)
		while (*argv)
			printf("%s\t", *argv++);
	printf("\n");
	current = content->redirections;
	while (current)
	{
		printf("%d\t%s\n", getredirtype(current), getredirstr(current));
		current = current->next;
	}
	printf("\n\n");
}
