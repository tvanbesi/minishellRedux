/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operatorsanity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 15:14:13 by user42            #+#    #+#             */
/*   Updated: 2021/03/09 15:36:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	operatorsanity(t_list *token)
{
	t_list	*current;

	current = token;
	if (current && gettokentype(current) == OPERATOR
	&& ispipeorsemicolon(current))
		return (-1);
	while (current)
	{
		if (gettokentype(current) == OPERATOR)
		{
			if (!isvalidoperator(current))
				return (-1);
			else if (isrediroperator(current) &&
			(!current->next || gettokentype(current->next) == OPERATOR))
				return (-1);
			else if (current->next && gettokentype(current->next) == OPERATOR
			&& !isrediroperator(current->next))
				return (-1);
		}
		current = current->next;
	}
	if (ft_lstlast(token) && gettokentype(ft_lstlast(token)) == OPERATOR
	&& ft_strncmp(gettokenstr(ft_lstlast(token)), ";", 2))
		return (-1);
	return (0);
}
