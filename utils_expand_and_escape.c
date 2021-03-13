/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand_and_escape.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 18:07:13 by user42            #+#    #+#             */
/*   Updated: 2021/03/13 15:31:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	restempty(char *s, t_parsedata *pd)
{
	if (!s[0])
		return (1);
	if (!pd->qt && isquote(s[0]))
		return (1);
	return (0);
}

static int
	closequote(t_list **r, char *src, t_parsedata *pd)
{
	if (pd->qt && pd->qt == src[pd->i])
	{
		pd->qt = 0;
		pd->i++;
		if (!ft_strlen(pd->buf))
		{
			if (src[pd->i] == '\0')
			{
				if (addemptytoken(r) == -1)
					return (-1);
			}
			else if (src[pd->i] == '$')
				pd->addempty = 1;
		}
		return (0);
	}
	return (1);
}

static int
	escape(char *src, t_parsedata *pd)
{
	if (src[pd->i] == '\\' && (!pd->qt
	|| (pd->qt == '\"' && isspecialchar(src[pd->i + 1]))))
	{
		pd->buf[pd->j++] = src[++(pd->i)];
		pd->i++;
		return (1);
	}
	return (0);
}

int
	expandloop(t_list **r, char *src, t_parsedata *pd, t_list *env)
{
	if (!pd->qt && isquote(src[pd->i]))
		pd->qt = src[pd->i++];
	else if ((pd->r = closequote(r, src, pd)) <= 0)
		;
	else if (escape(src, pd))
		;
	else if (pd->qt != '\'' && src[pd->i] == '$'
	&& (canbeexpanded(src[pd->i + 1]) || restempty(&src[pd->i + 1], pd)))
	{
		if (expand(r, src, pd, env) == -1)
			return (-1);
	}
	else if (!pd->qt && ft_isspht(src[pd->i]))
	{
		if (addtokenexpanded(r, pd->buf) == -1)
			return (-1);
		while (ft_isspht(src[pd->i]))
			pd->i++;
		ft_bzero(pd->buf, pd->idlen + 1);
		pd->j = 0;
	}
	else
		pd->buf[pd->j++] = src[pd->i++];
	return (pd->r);
}
