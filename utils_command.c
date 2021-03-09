/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 10:34:27 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/09 16:28:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	tokentoargv(t_list *current, t_list **argv)
{
	t_list	*token;
	t_token	*content;

	while (current
	&& !(gettokentype(current) == OPERATOR && ispipeorsemicolon(current)))
	{
		if (gettokentype(current) == OPERATOR && isrediroperator(current))
			current = current->next;
		else if (gettokentype(current) == WORD)
		{
			if (!(content = tokendup(current->content)))
				return (-1);
			if (!(token = ft_lstnew(content)))
			{
				free(content);
				return (-1);
			}
			ft_lstadd_back(argv, token);
		}
		current = current->next;
	}
	return (0);
}

int
	assignargv(t_list *token, t_list *command)
{
	t_list		*argv;
	t_command	*commandcontent;

	commandcontent = command->content;
	argv = NULL;
	if (tokentoargv(token, &argv) == -1)
		return (-1);
	commandcontent->argv = argv;
	return (0);
}
