/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 15:06:13 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/01 16:23:31 by user42           ###   ########.fr       */
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
	content->redirections = NULL;
	if (!(command = ft_lstnew(content)))
		free(content);
	return (command);
}

static t_list
	*newredir(char *s)
{
	t_list		*redir;
	t_redir		*content;
	int			type;

	type = -1;
	if (!ft_strncmp(s, "<", 2))
		type = REDIRIN;
	else if (!ft_strncmp(s, ">", 2))
		type = REDIRTRUNC;
	else if (!ft_strncmp(s, ">>", 3))
		type = REDIRAPPEND;
	if (!(content = malloc(sizeof(*content))))
		return (NULL);
	content->type = type;
	content->fd_str = NULL;
	if (!(redir = ft_lstnew(content)))
		free(content);
	return (redir);
}

static void
	*clear(t_list **acommand, int parserror)
{
	ft_lstclear(acommand, delcommand);
	if (parserror)
	{
		g_exitstatus = EXIT_STAT_ERRORPARSE;
		puterror(ERROR_PARSE);
	}
	else
		puterror(strerror(errno));
	return (NULL);
}

static int
	operatorsanity(t_list *token)
{
	t_list	*current;

	current = token;
	while (current)
	{
		if (gettokentype(token) == OPERATOR && !isvalidoperator(token))
			return (0);
		current = current->next;
	}
	return (1);
}

t_list
	*makecommands(t_list *token)
{
	t_list		*r;
	t_list		*command;
	t_command	*content;
	t_list		*redir;
	t_list		*current;
	t_list		*currentcpy;

	if (!operatorsanity(token))
		return (clear(NULL, 1));
	r = NULL;
	current = token;
	while (current)
	{
		if (!(command = newcommand(gettokencommandtype(current))))
			return (error(strerror(errno)));
		content = command->content;
		currentcpy = current;
		if (gettokentype(current) == OPERATOR && ispipeorsemicolon(current))
			return (clear(&command, 1));
		while (current && !(gettokentype(current) == OPERATOR && ispipeorsemicolon(current)))
		{
			if (gettokentype(current) == OPERATOR && isrediroperator(current))
			{
				if (!(redir = newredir(gettokenstr(current))))
					return (clear(&command, 0));
				if (getredirtype(redir) == -1)
					return (clear(&command, 1));
				current = current->next;
				if (!current || gettokentype(current) == OPERATOR)
					return (clear(&command, 1));
				if (!(((t_redir*)redir->content)->fd_str = ft_strdup(gettokenstr(current))))
					return (clear(&command, 0));
				ft_lstadd_back(&content->redirections, redir);
			}
			current = current->next;
		}
		current = currentcpy;
		while (current && !(gettokentype(current) == OPERATOR && ispipeorsemicolon(current)))
		{
			if (gettokentype(current) == WORD)
			{
				if (!getcmd(command))
				{
					if (!(content->cmd = ft_strdup(gettokenstr(current))))
						return (clear(&command, 0));
				}
				else
				{
					if (assignargv(current, command) == -1)
						return (clear(&command, 0));
					else
						break ;
				}
			}
			else if (gettokentype(current) == OPERATOR && isrediroperator(current))
				current = current->next;
			current = current->next;
		}
		ft_lstadd_back(&r, command);
		while (current && !(gettokentype(current) == OPERATOR && ispipeorsemicolon(current)))
			current = current->next;
		current = current ? current->next : current;
	}
	return (r);
}
