/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_gettoken.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 10:29:31 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/07 22:06:29 by user42           ###   ########.fr       */
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

static t_list
	*nextoperator(t_list *token)
{
	t_list	*current;

	current = token;
	while (current)
	{
		if (gettokentype(current) == OPERATOR)
			return (current);
		current = current->next;
	}
	return (current);
}

int
	gettokencommandtype(t_list *token)
{
	t_token	*content;

	token = nextoperator(token);
	while (token)
	{
		content = token->content;
		if (!ft_strncmp(content->s, ";", 2))
			return (SIMPLE);
		else if (!ft_strncmp(content->s, "|", 2))
			return (PIPE);
		token = nextoperator(token->next);
	}
	if (!token)
		return (SIMPLE);
	return (-1);
}
