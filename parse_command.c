/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 15:06:13 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/02/09 14:04:23 by user42           ###   ########.fr       */
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
	syntaxsanity(t_list *command)
{
	if (!command)
		return (1);
	command = ft_lstlast(command);
	if (getcommandtype(command) == SIMPLE)
		return (1);
	g_exitstatus = EXIT_STAT_ERRORPARSE;
	puterror(ERROR_PARSE);
	return (0);
}

t_list
	*makecommands(t_list *token)
{
	t_list	*r;
	t_list	*command;

	r = NULL;
	while (token)
	{
		if (!(command = newcommand(gettokencommandtype(token))))
			return (error(strerror(errno)));
		if (gettokentype(token) == WORD)
		{
			assigncmd(token, command);
			if (!getcmd(command) || assignargv(token, command) == -1)
			{
				ft_lstdelone(command, delcommand);
				free(command);
				return (error(strerror(errno)));
			}
		}
		ft_lstadd_back(&r, command);
		token = skipwords(token);
	}
	if (!syntaxsanity(r))
		ft_lstclear(&r, delcommand);
	return (r);
}
