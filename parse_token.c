/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 17:40:07 by user42            #+#    #+#             */
/*   Updated: 2021/03/09 22:31:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	quote(int *qt, int c)
{
	if (!*qt && isquote(c))
		*qt = c;
	else if (*qt && *qt == c)
		*qt = 0;
}

static int
	escape(char *input, t_parsedata *pd)
{
	if (input[pd->i] == '\\')
	{
		if (!input[pd->i + 1])
			return (-1);
		pd->i += 2;
		pd->l += 2;
	}
	return (0);
}

static void
	initparsedata(t_parsedata *pd)
{
	pd->s = 0;
	pd->i = 0;
	pd->l = 1;
	pd->qt = 0;
}

static void
	inc(t_parsedata *pd)
{
	pd->i++;
	pd->l++;
}

t_list
	*parse_token(char *input)
{
	t_list			*r;
	t_parsedata		pd;

	r = NULL;
	initparsedata(&pd);
	if (!input)
		return (NULL);
	while (input[pd.i])
	{
		quote(&pd.qt, input[pd.i]);
		if (escape(input, &pd) == -1)
			return (errorparse(&r));
		else if (!pd.qt && ismetachar(input[pd.i]))
		{
			if (addword(&r, input, &pd) == -1)
				return (fail(&r));
		}
		else
			inc(&pd);
	}
	if (addtoken(&r, &input[pd.s], pd.l - 1, WORD) == -1)
		return (fail(&r));
	if (operatorsanity(r) == -1)
		return (errorparse(&r));
	return (r);
}
