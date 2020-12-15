/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 15:06:13 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/14 19:14:08 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list
	*newcommand(int type)
{
	t_list		*command;
	t_command	*content;

	if (!(content = malloc(sizeof(*content))))
		return (NULL);
	content->type = type;
	content->cmd = NULL;
	content->argv = NULL;
	if (!(command = ft_lstnew(content)))
		free(content);
	return (command);
}

static t_list
	*skipmeta(t_list *token)
{
	t_list	*current;

	current = token;
	while (current)
	{
		if (gettokentype(current) != METACHARACTER)
			return (current);
		current = current->next;
	}
	return (NULL);
}

static t_list
	*skipcommand(t_list *token)
{
	t_list	*current;

	current = token;
	while (current)
	{
		if (gettokentype(current) == OPERATOR)
			return (current->next);
		current = current->next;
	}
	return (NULL);
}

t_list
	*makecommands(t_list *tokens)
{
	t_list	*r;
	t_list	*current;
	t_list	*command;

	r = NULL;
	current = tokens;
	while (current)
	{
		current = skipmeta(current);
		if (!(command = newcommand(gettokencommandtype(current))))
			return (error(strerror(errno)));
		if (gettokentype(current) == WORD)
			assigncmd(current, command);
		else
		{
			ft_lstdelone(command, delcommand);
			return (error(ERROR_PARSE));
		}
		if (assignargv(current->next, command) == -1)
		{
			ft_lstdelone(command, delcommand);
			return (error(strerror(errno)));
		}
		ft_lstadd_back(&r, command);
		current = skipcommand(current);
	}
	return (r);
}
