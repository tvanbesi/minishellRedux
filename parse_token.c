/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 11:35:57 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/01/12 13:20:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	quote(int qt, int c)
{
	if (!qt && isquote(c))
		qt = c;
	else if (qt && c == qt)
		qt = 0;
	return (qt);
}

static int
	tokenizeword(char *input, t_list **atoken, t_parsedata *pd, t_list *env)
{
	pd->l--;
	if (addword(atoken, &input[pd->i - pd->l], pd->l, env) == -1)
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

static void
	*unclosedqt(void)
{
	g_exitstatus = EXIT_STAT_ERRORPARSE;
	return (error(ERROR_PARSE));
}

t_list
	*tokenize(char *input, t_list *env)
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
		if (!(pd.qt = quote(pd.qt, input[pd.i])) && ismetachar(input[pd.i]))
		{
			if (tokenizeword(input, &r, &pd, env) == -1)
				return (NULL);
		}
		else
			pd.i++;
	}
	if (addword(&r, &input[pd.i - pd.l], pd.l, env) == -1)
		return (NULL);
	if (pd.qt)
		return (unclosedqt());
	return (r);
}
