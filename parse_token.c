/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 17:40:07 by user42            #+#    #+#             */
/*   Updated: 2021/03/08 22:57:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	operatorsanity(t_list *token)
{
	t_list	*current;

	current = token;
	while (current)
	{
		if (gettokentype(current) == OPERATOR && !isvalidoperator(current))
			return (-1);
		current = current->next;
	}
	return (0);
}

static void
	*errorparse(t_list **token)
{
	ft_lstclear(token, deltoken);
	puterror(ERROR_PARSE);
	g_exitstatus = EXIT_STAT_ERRORPARSE;
	return (NULL);
}

t_list
	*parse_token(char *input)
{
	t_list			*r;
	unsigned int	s;
	int				i;
	size_t			l;
	int				qt;

	r = NULL;
	s = 0;
	i = 0;
	l = 1;
	qt = 0;
	if (!input)
		return (NULL);
	while (input[i])
	{
		if (!qt && isquote(input[i]))
			qt = input[i];
		else if (qt && qt == input[i])
			qt = 0;
		if (input[i] == '\\')
		{
			if (!input[i + 1])
				return (errorparse(&r));
			i += 2;
			l += 2;
			continue ;
		}
		if (!qt && ismetachar(input[i]))
		{
			if (addtoken(&r, input, s, l - 1, WORD) == -1)
				return (NULL); // clear all that shit
			l = 0;
			s = i;
			while (ismetachar(input[i]))
			{
				i++;
				l++;
			}
			if (addtoken(&r, input, s, l, OPERATOR) == -1)
				return (NULL);
			s = i;
			l = 1;
		}
		else
		{
			i++;
			l++;
		}
	}
	if (addtoken(&r, input, s, l - 1, WORD) == -1)
		return (NULL);
	if (operatorsanity(r) == -1
	|| (gettokentype(r) == OPERATOR && ispipeorsemicolon(r)))
		return (errorparse(&r));
	return (r);
}
