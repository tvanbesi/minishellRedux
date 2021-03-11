/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 23:06:56 by user42            #+#    #+#             */
/*   Updated: 2021/03/11 00:43:33 by user42           ###   ########.fr       */
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

static void
	*ret(t_list **r)
{
	puterror(strerror(errno));
	ft_lstclear(r, delcommand);
	return (NULL);
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
			return (ret(&r));
		if (parse_redircmd(token, command) < 0)
			return (ret(&r));
		if (parse_cmd(token, command) < 0)
			return (ret(&r));
		ft_lstadd_back(&r, command);
		while (token && !(gettokentype(token) == OPERATOR
		&& ispipeorsemicolon(token)))
			token = token->next;
		token = token ? token->next : token;
	}
	return (r);
}
