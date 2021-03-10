/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getidlen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:49:33 by user42            #+#    #+#             */
/*   Updated: 2021/03/10 16:15:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	increment(ssize_t *r, size_t *i, char *mode, char *s)
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

static int
	incparam(ssize_t *r, char *param)
{
	if (!(param = ft_strtrim(param, " \t")))
		return (-1);
	*r += ft_strlen(param);
	free(param);
	return (0);
}

ssize_t
	getidlen(char *s, t_list *env)
{
	ssize_t	r;
	size_t	i;
	char	*param;

	r = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			if (s[i + 1] == '?')
				increment(&r, &i, "exitstatus", s);
			else
			{
				if ((param = getidentifier(&s[++i], env)))
					if (incparam(&r, param) == -1)
						return (-1);
				increment(&r, &i, "param", s);
			}
		}
		else
			increment(&r, &i, "default", s);
	}
	return (r);
}
