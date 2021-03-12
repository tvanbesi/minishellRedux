/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_escape.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 15:48:01 by user42            #+#    #+#             */
/*   Updated: 2021/03/12 17:44:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	initpd(t_parsedata *pd, char *src, t_list *env)
{
	pd->i = 0;
	pd->j = 0;
	pd->qt = 0;
	pd->idlen = getidlen(src, env);
}

static int
	parse_expansion(t_list **atoken, char *buf, char *param, t_parsedata *pd)
{
	int	i;

	i = 0;
	while (param[i])
	{
		if (!pd->qt && ft_isspht(param[i]))
		{
			if (addtokenexpanded(atoken, buf) == -1)
				return (-1);
			while (ft_isspht(param[i]))
				i++;
			ft_bzero(buf, pd->idlen + 1);
			pd->j = 0;
		}
		else
			buf[pd->j++] = param[i++];
	}
	return (0);
}

static int
	expand(t_list **atoken, char *src, t_parsedata *pd, t_list *env)
{
	if (src[pd->i + 1] == '?')
	{
		if (!(pd->param = ft_itoa(g_exitstatus)))
			return (-1);
		pd->j += ft_strlcat(pd->buf, pd->param, pd->idlen + 1);
		free(pd->param);
		pd->i += 2;
	}
	else if (ft_isalpha(src[pd->i + 1]) || src[pd->i + 1] == '_')
	{
		if ((pd->param = getidentifier(&src[pd->i + 1], env)))
			if (parse_expansion(atoken, pd->buf, pd->param, pd) == -1)
				return (-1);
		pd->i++;
		while (ft_isalnum(src[pd->i]) || src[pd->i] == '_')
			pd->i++;
	}
	else if (isquote(src[pd->i + 1]))
		pd->i++;
	else if (ft_isdigit(src[pd->i + 1]))
		pd->i += 2;
	else
		pd->buf[pd->j++] = src[pd->i++];
	return (0);
}

static int
	restempty(char *s, t_parsedata *pd)
{
	if (!s[0])
		return (1);
	if (!pd->qt && isquote(s[0]))
		return (1);
	return (0);
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
	{
		if (!pd.qt && isquote(src[pd.i]))
			pd.qt = src[pd.i++];
		else if (pd.qt && pd.qt == src[pd.i])
		{
			pd.qt = 0;
			pd.i++;
			if (src[pd.i] == '\0' && !ft_strlen(pd.buf))
				if (addemptytoken(&r) == -1)
				{
					free(pd.buf);
					ft_lstclear(&r, deltoken);
					return (NULL);
				}
		}
		else if (src[pd.i] == '\\' && (!pd.qt
		|| (pd.qt == '\"' && isspecialchar(src[pd.i + 1]))))
		{
			pd.buf[pd.j++] = src[++(pd.i)];
			pd.i++;
		}
		else if (pd.qt != '\'' && src[pd.i] == '$'
		&& (canbeexpanded(src[pd.i + 1]) || restempty(&src[pd.i + 1], &pd)))
		{
			if (expand(&r, src, &pd, env) == -1)
			{
				free(pd.buf);
				ft_lstclear(&r, deltoken);
				return (NULL);
			}
		}
		else if (!pd.qt && ft_isspht(src[pd.i]))
		{
			if (addtokenexpanded(&r, pd.buf) == -1)
			{
				free(pd.buf);
				ft_lstclear(&r, deltoken);
				return (NULL);
			}
			while (ft_isspht(src[pd.i]))
				pd.i++;
			ft_bzero(pd.buf, pd.idlen + 1);
			pd.j = 0;
		}
		else
			pd.buf[pd.j++] = src[pd.i++];
	}
	if (ft_strlen(pd.buf))
	{
		if (addtokenexpanded(&r, pd.buf) == -1)
		{
			free(pd.buf);
			ft_lstclear(&r, deltoken);
			return (NULL);
		}
	}
	else if (src[0] == '\0')
	{
		if (addemptytoken(&r) == -1)
		{
			free(pd.buf);
			ft_lstclear(&r, deltoken);
			return (NULL);
		}
	}
	else if (r == NULL)
		if (addnulltoken(&r) == -1)
		{
			free(pd.buf);
			ft_lstclear(&r, deltoken);
			return (NULL);
		}
	free(pd.buf);
	return (r);
}
