/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_escape.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 15:48:01 by user42            #+#    #+#             */
/*   Updated: 2021/03/13 15:27:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	initpd(t_parsedata *pd, char *src, t_list *env)
{
	pd->i = 0;
	pd->j = 0;
	pd->qt = 0;
	pd->r = 0;
	pd->idlen = getidlen(src, env);
	pd->addempty = 0;
}

static void
	*ret(char *buf, t_list **r)
{
	free(buf);
	ft_lstclear(r, deltoken);
	return (NULL);
}

t_list
	*expand_and_escape(char *src, t_list *env)
{
	t_list		*r;
	t_parsedata	pd;

	r = NULL;
	initpd(&pd, src, env);
	if (!(pd.buf = ft_calloc(pd.idlen + 1, sizeof(char))))
		return (NULL);
	while (src[pd.i])
		if (expandloop(&r, src, &pd, env) == -1)
			return (ret(pd.buf, &r));
	if (ft_strlen(pd.buf))
	{
		if (addtokenexpanded(&r, pd.buf) == -1)
			return (ret(pd.buf, &r));
	}
	else if (src[0] == '\0')
	{
		if (addemptytoken(&r) == -1)
			return (ret(pd.buf, &r));
	}
	else if (r == NULL)
		if (addnulltoken(&r) == -1)
			return (ret(pd.buf, &r));
	free(pd.buf);
	return (r);
}
