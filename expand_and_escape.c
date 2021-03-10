/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_escape.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 15:48:01 by user42            #+#    #+#             */
/*   Updated: 2021/03/10 16:11:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	escape(int *i, int *j, char *dst, char *src)
{
	(*i)++;
	dst[*j] = src[*i];
	(*j)++;
	(*i)++;
}

static int
	nulltoken(int qt, int l, char **s, int c)
{
	if (!qt && !l && !c)
	{
		free(*s);
		*s = NULL;
		return (1);
	}
	return (0);
}

static int
	quote(int *qt, int c, int *i)
{
	if (!*qt && isquote(c))
	{
		*qt = c;
		(*i)++;
		return (1);
	}
	else if (*qt && *qt == c)
	{
		*qt = 0;
		(*i)++;
		return (1);
	}
	return (0);
}

static void
	initpd(t_parsedata *pd, int idlen)
{
	pd->i = 0;
	pd->j = 0;
	pd->qt = 0;
	pd->idlen = idlen;
}

int
	expand_and_escape(char **dst, char *src, int idlen, t_list *env)
{
	t_parsedata	pd;

	initpd(&pd, idlen);
	while (src[pd.i])
	{
		if (quote(&pd.qt, src[pd.i], &pd.i))
			;
		else if (shouldescape(src[pd.i], src[pd.i + 1], pd.qt))
			escape(&pd.i, &pd.j, *dst, src);
		else if (shouldexpand(src[pd.i], pd.qt))
		{
			if (expansion(*dst, &(src[pd.i++]), env, &pd) == -1)
				return (-1);
			skipidentifier(src, &pd);
			if (nulltoken(pd.qt, ft_strlen(*dst), dst, src[pd.i]))
				return (0);
			pd.j = ft_strlen(*dst);
		}
		else
			(*dst)[pd.j++] = src[pd.i++];
	}
	return (0);
}
