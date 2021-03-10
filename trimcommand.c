/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimcommand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 23:53:25 by user42            #+#    #+#             */
/*   Updated: 2021/03/10 23:55:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	ret(t_token *content, t_list **r)
{
	ft_lstclear(r, deltoken);
	deltoken(content);
	return (-1);
}

int
	trimcommand(t_list **argv)
{
	t_list	*r;
	t_token	*content;
	t_list	*tmp;
	t_list	*current;

	r = NULL;
	if (!argv)
		return (0);
	current = *argv;
	while (current)
	{
		if (gettokenstr(current))
		{
			if (!(content = tokendup(current->content)))
				ret(content, &r);
			if (!(tmp = ft_lstnew(content)))
				ret(content, &r);
			ft_lstadd_back(&r, tmp);
		}
		current = current->next;
	}
	ft_lstclear(argv, deltoken);
	*argv = r;
	return (0);
}
