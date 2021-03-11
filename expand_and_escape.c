/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_escape.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 15:48:01 by user42            #+#    #+#             */
/*   Updated: 2021/03/11 01:47:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	escape(int *i, int *j, char *dst, char *src)
{
	dst[(*j)++] = src[(*i)++];
	dst[(*j)++] = src[(*i)++];
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
	(void)i;
	if (!*qt && isquote(c))
	{
		*qt = c;
		return (1);
	}
	else if (*qt && *qt == c)
	{
		*qt = 0;
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

void
	expand_and_escape(char **dst, char *src, int idlen, t_list *env)
{
	t_parsedata	pd;

	initpd(&pd, idlen);
	while (src[pd.i])
	{
		if (quote(&pd.qt, src[pd.i], &pd.i))
			;
		if (shouldescape(src[pd.i], src[pd.i + 1], pd.qt))
			escape(&pd.i, &pd.j, *dst, src);
		else if (shouldexpand(src[pd.i], src[pd.i + 1], pd.qt))
		{
			expansion(*dst, &(src[pd.i++]), env, &pd);
			if (ft_isdigit(src[pd.i]) || src[pd.i] == '?')
				pd.i++;
			else
				while (ft_isalnum(src[pd.i]) || src[pd.i] == '_')
					pd.i++;
			if (nulltoken(pd.qt, ft_strlen(*dst), dst, src[pd.i]))
				return ;
			pd.j = ft_strlen(*dst);
		}
		else
			(*dst)[pd.j++] = src[pd.i++];
	}
}
