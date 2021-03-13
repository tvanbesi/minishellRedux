/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operatorsanity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 15:14:13 by user42            #+#    #+#             */
/*   Updated: 2021/03/13 11:23:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	errorparseoperator(t_list *token)
{
	char	*tmp;

	tmp = gettokenstr(token);
	ft_putstr_fd(ERROR_PARSE, STDERR);
	ft_putstr_fd(" near unexpected symbol : ", STDERR);
	ft_putchar_fd(tmp[0], STDERR);
	write(STDERR, "\n", 1);
	return (-1);
}

int
	operatorsanity(t_list *token)
{
	t_list	*current;

	current = token;
	if (current && gettokentype(current) == OPERATOR
	&& ispipeorsemicolon(current))
		return (errorparseoperator(current));
	while (current)
	{
		if (gettokentype(current) == OPERATOR)
		{
			if (!isvalidoperator(current))
				return (errorparseoperator(current));
			else if (isrediroperator(current) &&
			(!current->next || gettokentype(current->next) == OPERATOR))
				return (errorparseoperator(current));
			else if (current->next && gettokentype(current->next) == OPERATOR
			&& !isrediroperator(current->next))
				return (errorparseoperator(current));
		}
		current = current->next;
	}
	if (ft_lstlast(token) && gettokentype(ft_lstlast(token)) == OPERATOR
	&& ft_strncmp(gettokenstr(ft_lstlast(token)), ";", 2))
		return (errorparseoperator(ft_lstlast(token)));
	return (0);
}
