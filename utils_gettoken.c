/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_gettoken.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 10:29:31 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/14 19:13:27 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	gettokentype(t_list *token)
{
	t_token	*content;

	content = token->content;
	return (content->type);
}

char
	*gettokenstr(t_list *token)
{
	t_token	*content;

	content = token->content;
	return (content->s);
}

int
	getoperatortype(t_list *token)
{
	t_token	*content;

	content = token->content;
	if (content->s[0] == ';')
		return (SIMPLE);
	else if (content->s[0] == '|')
		return (PIPE);
	else if (content->s[0] == '>' || content->s[0] == '<')
		return (REDIRECTION);
	else
		return (-1);
}

int
	gettokencommandtype(t_list *token)
{
	t_list	*current;

	current = token;
	while (current)
	{
		if (gettokentype(current) == OPERATOR)
			return (getoperatortype(current));
		current = current->next;
	}
	return (SIMPLE);
}

