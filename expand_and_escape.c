/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_escape.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 15:48:01 by user42            #+#    #+#             */
/*   Updated: 2021/03/12 16:29:55 by user42           ###   ########.fr       */
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
	expand(t_list **atoken, char *buf, char *src, t_parsedata *pd, t_list *env)
{
	char	*param;

	if (src[pd->i + 1] == '?')
	{
		if (!(param = ft_itoa(g_exitstatus)))
			return (-1);
		pd->j += ft_strlcat(buf, param, pd->idlen + 1);
		free(param);
		pd->i += 2;
	}
	else if (ft_isalpha(src[pd->i + 1]) || src[pd->i + 1] == '_')
	{
		if ((param = getidentifier(&src[pd->i + 1], env)))
		{
			if (parse_expansion(atoken, buf, param, pd) == -1)
				return (-1);
		}
		pd->i++;
		while (ft_isalnum(src[pd->i]) || src[pd->i] == '_')
			pd->i++;
	}
	else if (isquote(src[pd->i + 1]))
		pd->i++;
	else if (ft_isdigit(src[pd->i + 1]))
		pd->i += 2;
	else
		buf[pd->j++] = src[pd->i++];
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
	t_list	*r;
	char	*buf;
	t_parsedata	pd;

	r = NULL;
	initpd(&pd, src, env);
	if (!(buf = ft_calloc(pd.idlen + 1, sizeof(char))))
		return (NULL);
	while (src[pd.i])
	{
		if (!pd.qt && isquote(src[pd.i]))
			pd.qt = src[pd.i++];
		else if (pd.qt && pd.qt == src[pd.i])
		{
			pd.qt = 0;
			pd.i++;
			if (src[pd.i] == '\0' && !ft_strlen(buf))
				if (addemptytoken(&r) == -1)
				{
					free(buf);
					ft_lstclear(&r, deltoken);
					return (NULL);
				}
		}
		else if (src[pd.i] == '\\' && (!pd.qt
		|| (pd.qt == '\"' && isspecialchar(src[pd.i + 1]))))
		{
			buf[pd.j++] = src[++(pd.i)];
			pd.i++;
		}
		else if (pd.qt != '\'' && src[pd.i] == '$'
		&& (canbeexpanded(src[pd.i + 1]) || restempty(&src[pd.i + 1], &pd)))
		{
			if (expand(&r, buf, src, &pd, env) == -1)
			{
				free(buf);
				ft_lstclear(&r, deltoken);
				return (NULL);
			}
		}
		else if (!pd.qt && ft_isspht(src[pd.i]))
		{
			if (addtokenexpanded(&r, buf) == -1)
			{
				free(buf);
				ft_lstclear(&r, deltoken);
				return (NULL);
			}
			while (ft_isspht(src[pd.i]))
				pd.i++;
			ft_bzero(buf, pd.idlen + 1);
			pd.j = 0;
		}
		else
			buf[pd.j++] = src[pd.i++];
	}
	if (ft_strlen(buf))
	{
		if (addtokenexpanded(&r, buf) == -1)
		{
			free(buf);
			ft_lstclear(&r, deltoken);
			return (NULL);
		}
	}
	else if (src[0] == '\0')
	{
		if (addemptytoken(&r) == -1)
		{
			free(buf);
			ft_lstclear(&r, deltoken);
			return (NULL);
		}
	}
	else if (r == NULL)
		if (addnulltoken(&r) == -1)
		{
			free(buf);
			ft_lstclear(&r, deltoken);
			return (NULL);
		}
	free(buf);
	return (r);
}

/*
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
	quote(int *qt, int c)
{
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

void
	expand_and_escape(char **dst, char *src, int idlen, t_list *env)
{
	t_parsedata	pd;

	initpd(&pd, idlen);
	while (src[pd.i])
	{
		if (quote(&pd.qt, src[pd.i]))
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
*/
