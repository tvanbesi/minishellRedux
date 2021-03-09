/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 23:06:56 by user42            #+#    #+#             */
/*   Updated: 2021/03/09 15:32:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list
	*newcommand(int type)
{
	t_list		*command;
	t_command	*content;

	if (!(content = malloc(sizeof(*content))))
		return (NULL);
	content->type = type;
	content->argv = NULL;
	content->redirections = NULL;
	if (!(command = ft_lstnew(content)))
		free(content);
	return (command);
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
			if (assignargv(token, command) == -1)
				return (-1);
			return (0);
		}
		else if (gettokentype(token) == OPERATOR && isrediroperator(token))
			token = token->next;
		token = token->next;
	}
	return (0);
}

static int
	parse_redircmd(t_list *token, t_list *command)
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
				return (-1);
			if (getredirtype(redir) == -1)
				return (-2);
			token = token->next;
			if (!token || gettokentype(token) == OPERATOR)
				return (-2);
			redircontent = redir->content;
			if (!(redircontent->fd_str = tokendup(token->content)))
				return (-1);
			ft_lstadd_back(&content->redirections, redir);
		}
		token = token->next;
	}
	return (0);
}

t_list
	*parse_command(t_list *token)
{
	t_list	*r;
	t_list	*command;

	r = NULL;
	if (!token)
		return (NULL);
	while (token)
	{
		if (!(command = newcommand(gettokencommandtype(token))))
			return (NULL);
		if (parse_redircmd(token, command) < 0)
			printf("error redir\n");
		if (parse_cmd(token, command) < 0)
			printf("error command parse\n");
		ft_lstadd_back(&r, command);
		while (token && !(gettokentype(token) == OPERATOR
		&& ispipeorsemicolon(token)))
			token = token->next;
		token = token ? token->next : token;
	}
	return (r);
}
