/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 15:06:13 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/17 14:17:12 by tvanbesi         ###   ########.fr       */
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
	*skipwords(t_list *token)
{
	t_list	*current;

	current = token;
	while (current)
	{
		if (gettokentype(current) != WORD)
			return (current->next);
		current = current->next;
	}
	return (current);
}

static int
	commandsanity(t_list *command)
{
	t_list	*current;

	current = command;
	while (current)
	{
		if (!getcmd(current))
			return (0);
		current = current->next;
	}
	command = ft_lstlast(command);
	return (getcommandtype(command) == SIMPLE);
}

t_list
	*makecommands(t_list *token)
{
	t_list	*r;
	t_list	*current;
	t_list	*command;
	int		commandtype;

	r = NULL;
	current = token;
	while (current)
	{
		commandtype = gettokencommandtype(current);
		if (!(command = newcommand(commandtype)))
			return (error(strerror(errno)));
		if (gettokentype(current) == WORD)
			assigncmd(current, command);
		if (assignargv(current->next, command) == -1)
		{
			ft_lstdelone(command, delcommand);
			return (error(strerror(errno)));
		}
		ft_lstadd_back(&r, command);
		current = skipwords(current);
	}
	if (!commandsanity(r))
	{
		puterror(ERROR_PARSE);
		ft_lstclear(&r, delcommand);
	}
	return (r);
}
