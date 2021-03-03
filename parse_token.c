/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 11:35:57 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/03 15:09:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	quote(t_parsedata *pd, int c)
{
	if (!pd->qt && isquote(c))
		pd->qt = c;
	else if (pd->qt && c == pd->qt)
		pd->qt = 0;
}

static int
	tokenizeword(char *input, t_list **atoken, t_parsedata *pd)
{
	pd->l--;
	if (addword(atoken, &input[pd->i - pd->l], pd->l) == -1)
		return (-1);
	if (addmetachar(atoken, &input[pd->i]) == -1)
		return (-1);
	while (ismetachar(input[pd->i]))
		pd->i++;
	pd->l = 0;
	return (0);
}

static void
	initparsedata(t_parsedata *pd)
{
	pd->i = 0;
	pd->l = 0;
	pd->qt = 0;
}

t_list
	*tokenize(char *input)
{
	t_list			*r;
	t_parsedata		pd;

	if (!input)
		return (NULL);
	r = NULL;
	initparsedata(&pd);
	while (input[pd.i])
	{
		pd.l++;
		if (pd.i > 0 && (input[pd.i - 1] != '\\' || pd.qt == '\''))
			quote(&pd, input[pd.i]);
		if (!pd.qt && ismetachar(input[pd.i]))
		{
			if (tokenizeword(input, &r, &pd) == -1)
				return (error(strerror(errno)));
		}
		else
			pd.i++;
	}
	if (addword(&r, &input[pd.i - pd.l], pd.l) == -1)
		return (error(strerror(errno)));
	return (r);
}
