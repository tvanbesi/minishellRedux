/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_gettoken.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 10:29:31 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/01/12 14:22:20 by user42           ###   ########.fr       */
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
	if (!token)
		return (SIMPLE);
	content = token->content;
	if (!ft_strncmp(content->s, ";", 2))
		return (SIMPLE);
	else if (!ft_strncmp(content->s, "|", 2))
		return (PIPE);
	else if (!ft_strncmp(content->s, ">", 2))
		return (REDIRTRUNC);
	else if (!ft_strncmp(content->s, "<", 2))
		return (REDIRIN);
	else if (!ft_strncmp(content->s, ">>", 3))
		return (REDIRAPPEND);
	else
		return (-1);
}
