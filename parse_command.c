/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 15:06:13 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/16 10:50:09 by tvanbesi         ###   ########.fr       */
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
		if ((commandtype = gettokencommandtype(current)) == -1)
			return (error(ERROR_PARSE));
		if (!(command = newcommand(commandtype)))
			return (error(strerror(errno)));
		if (gettokentype(current) == WORD)
			assigncmd(current, command);
		else
		{
			//Empty word for implicit stdin and stdout for redirection
			ft_lstdelone(command, delcommand);
			return (error(ERROR_PARSE));
		}
		if (assignargv(current->next, command) == -1)
		{
			ft_lstdelone(command, delcommand);
			return (error(strerror(errno)));
		}
		ft_lstadd_back(&r, command);
		current = skipwords(current);
	}
	return (r);
}
