/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 15:06:13 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/02 19:53:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	{
		g_exitstatus = EXIT_STAT_FAIL;
		puterror(strerror(errno));
	}
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
	current = ft_lstlast(token);
	if (gettokentype(current) == OPERATOR
	&& !ft_strncmp(gettokenstr(current), "|", 2))
		return (0);
	return (1);
}

static int
	parse_redir(t_list *token, t_list *command)
{
	t_list		*redir;
	t_command	*content;
	t_redir		*redircontent;

	content = command->content;
	while (token && !(gettokentype(token) == OPERATOR
	&& ispipeorsemicolon(token)))
	{
		if (gettokentype(token) == OPERATOR && isrediroperator(token))
		{
			if (!(redir = newredir(gettokenstr(token))))
				return (1);
			if (getredirtype(redir) == -1)
				return (2);
			token = token->next;
			if (!token || gettokentype(token) == OPERATOR)
				return (2);
			redircontent = redir->content;
			if (!(redircontent->fd_str = ft_strdup(gettokenstr(token))))
				return (1);
			ft_lstadd_back(&content->redirections, redir);
		}
		token = token->next;
	}
	return (0);
}

static int
	parse_cmd(t_list *token, t_list *command)
{
	t_command	*content;

	content = command->content;
	while (token && !(gettokentype(token) == OPERATOR
	&& ispipeorsemicolon(token)))
	{
		if (gettokentype(token) == WORD)
		{
			if (!getcmd(command))
			{
				if (!(content->cmd = ft_strdup(gettokenstr(token))))
					return (1);
			}
			else
			{
				if (assignargv(token, command) == -1)
					return (1);
				return (0);
			}
		}
		else if (gettokentype(token) == OPERATOR && isrediroperator(token))
			token = token->next;
		token = token->next;
	}
	return (0);
}

t_list
	*makecommands(t_list *token)
{
	t_list		*r;
	int			n;
	t_list		*command;

	if (!token)
		return (NULL);
	if (!operatorsanity(token))
		return (clear(NULL, 1));
	r = NULL;
	while (token)
	{
		if (!(command = newcommand(gettokencommandtype(token))))
			return (error(strerror(errno)));
		if (gettokentype(token) == OPERATOR && ispipeorsemicolon(token))
			return (clear(&command, 1));
		if (((n = parse_redir(token, command)) > 0)
		|| ((n = parse_cmd(token, command)) > 0))
			return (clear(&command, n - 1));
		ft_lstadd_back(&r, command);
		while (token && !(gettokentype(token) == OPERATOR
		&& ispipeorsemicolon(token)))
			token = token->next;
		token = token ? token->next : token;
	}
	return (r);
}
