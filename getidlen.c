/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getidlen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:49:33 by user42            #+#    #+#             */
/*   Updated: 2021/02/08 13:13:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	increment(size_t *r, size_t *i, char *mode)
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
}

size_t
	getidlen(char *s, t_list *env)
{
	size_t	r;
	size_t	i;
	char	*param;

	r = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			if (s[i + 1] == '?')
				increment(&r, &i, "exitstatus");
			else
			{
				param = getidentifier(&s[i + 1], env);
				if (param)
					r += ft_strlen(param);
				i++;
				while (ft_isalnum(s[i]) || s[i] == '_')
					i++;
			}
		}
		else
			increment(&r, &i, "default");
	}
	return (r);
}
