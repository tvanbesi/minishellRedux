/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 10:34:27 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/08 14:56:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void
	assigncmd(t_list *token, t_list *command)
{
	t_list		*current;
	t_command	*commandcontent;

	commandcontent = command->content;
	current = token;
	while (current && gettokentype(current) == WORD)
	{
		if (gettokenstr(current))
		{
			commandcontent->cmd = ft_strdup(gettokenstr(current));
			return ;
		}
		current = current->next;
	}
	commandcontent->cmd = NULL;
}

static int
	countargv(t_list *token)
{
	int		r;
	t_list	*current;

	r = 0;
	current = token;
	while (current)
	{
		if (gettokentype(current) == OPERATOR && isrediroperator(current))
			current = current->next;
		else if (gettokentype(current) == WORD && gettokenstr(current))
			r++;
		else if (gettokentype(current) == OPERATOR
		&& ispipeorsemicolon(current))
			return (r);
		current = current->next;
	}
	return (r);
}
*/
static int
	tokentoargv(t_list *current, t_list **argv)
{
	t_list	*token;
	t_token	*content;

	while (current && !(gettokentype(current) == OPERATOR && ispipeorsemicolon(current)))
	{
		if (gettokentype(current) == OPERATOR && isrediroperator(current))
			current = current->next;
		else if (gettokentype(current) == WORD)
		{
			if (!(content = tokendup(current->content)))
				return (-1);
			if (!(token = ft_lstnew(content)))
			{
				free(content);
				return (-1);
			}
			ft_lstadd_back(argv, token);
		}
		current = current->next;
	}
	return (0);
}

int
	assignargv(t_list *token, t_list *command)
{
	t_list		*argv;
	t_command	*commandcontent;

	commandcontent = command->content;
	argv = NULL;
	if (tokentoargv(token, &argv) == -1)
		return (-1);
	commandcontent->argv = argv;
	return (0);
}
