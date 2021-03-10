/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_expanded.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 19:37:25 by user42            #+#    #+#             */
/*   Updated: 2021/03/10 23:36:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	collapsestr(char *s, int i)
{
	ft_memmove(&s[i], &s[i + 1], ft_strlen(&s[i]) - 1);
	s[ft_strlen(s) - 1] = '\0';
}

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
		if (pd.escape)
		{
			inc(&pd);
			pd.escape = 0;
		}
		else if (!pd.qt && isquote(input[pd.i]))
		{
			pd.qt = input[pd.i];
			collapsestr(input, pd.i);
		}
		else if (pd.qt && input[pd.i] == pd.qt)
		{
			pd.qt = 0;
			collapsestr(input, pd.i);
			if (!input[pd.i] && pd.l == 1)
				addnulltoken(&r);
		}
		else if (input[pd.i] == '\\' && (!pd.qt || (pd.qt == '\"' && isspecialchar(input[pd.i + 1]))))
			escape(input, &pd);
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
