/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getidlen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:49:33 by user42            #+#    #+#             */
/*   Updated: 2021/03/11 12:48:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	increment(size_t *r, size_t *i, char *mode, char *s)
{
	if (!ft_strncmp(mode, "exitstatus", 10))
	{
		*r += 3;
		*i += 2;
	}
	else if (!ft_strncmp(mode, "default", 7))
	{
		*r += 1;
		*i += 1;
	}
	else if (!ft_strncmp(mode, "param", 6))
	{
		if (ft_isdigit(s[*i]))
			(*i)++;
		else
			while (ft_isalnum(s[*i]) || s[*i] == '_')
				(*i)++;
	}
}

static void
	incrementnoparam(size_t *r, size_t *i, char *s)
{
	*i += 2;
	(*r)++;
	if (ft_isdigit(s[*i]))
	{
		(*i)++;
		(*r)++;
	}
	else
		while (ft_isalnum(s[*i]) || s[*i] == '_')
		{
			(*i)++;
			(*r)++;
		}
}

static void
	addparamlen(size_t *r, size_t *i, char *s, t_list *env)
{
	char	*param;

	(*i)++;
	if ((param = getidentifier(&s[*i], env)))
		(*r) += ft_strlen(param);
	else
		(*r)++;
}

size_t
	getidlen(char *s, t_list *env)
{
	size_t	r;
	size_t	i;

	r = 1;
	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			if (s[i + 1] == '?')
				increment(&r, &i, "exitstatus", s);
			else
			{
				addparamlen(&r, &i, s, env);
				increment(&r, &i, "param", s);
			}
		}
		else if (s[i] == '\\' && s[i + 1] == '$')
			incrementnoparam(&r, &i, s);
		else
			increment(&r, &i, "default", s);
	}
	return (r);
}
