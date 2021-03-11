/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_expanded.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 19:37:25 by user42            #+#    #+#             */
/*   Updated: 2021/03/11 12:41:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	escape(char *input, t_parsedata *pd)
{
	collapsestr(input, pd->i);
	pd->escape = 1;
}

static void
	initparsedata(t_parsedata *pd)
{
	pd->s = 0;
	pd->i = 0;
	pd->l = 1;
	pd->qt = 0;
	pd->escape = 0;
}

static void
	inc(t_parsedata *pd)
{
	pd->i++;
	pd->l++;
	pd->escape = 0;
}

static int
	escape_and_quote(char *input, t_parsedata *pd, t_list **r)
{
	if (pd->escape)
	{
		inc(pd);
		return (1);
	}
	else if (openquote(input, pd) || closequote(input, pd, r))
		return (1);
	else if (input[pd->i] == '\\'
	&& (!pd->qt || (pd->qt == '\"'
	&& (isspecialchar(input[pd->i + 1]) || isquote(input[pd->i + 1])))))
	{
		escape(input, pd);
		return (1);
	}
	return (0);
}

t_list
	*parse_token_expanded(char *input)
{
	t_list			*r;
	t_parsedata		pd;

	r = NULL;
	initparsedata(&pd);
	if (!input)
		return (NULL);
	while (input[pd.i])
	{
		if (escape_and_quote(input, &pd, &r))
			;
		else if (!pd.qt && ft_isspht(input[pd.i]))
		{
			if (addwordexpanded(&r, input, &pd) == -1)
				return (fail(&r));
		}
		else
			inc(&pd);
	}
	if (addtokenexpanded(&r, &input[pd.s], pd.l - 1, WORD) == -1)
		return (fail(&r));
	return (r);
}
