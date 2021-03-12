/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_expanded.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 22:31:44 by user42            #+#    #+#             */
/*   Updated: 2021/03/12 14:26:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	loopcollapsestr(char *s, int i, int n)
{
	while (n-- > 0)
		collapsestr(s, i);
}

void
	collapsestr(char *s, int i)
{
	ft_memmove(&s[i], &s[i + 1], ft_strlen(&s[i]) - 1);
	s[ft_strlen(s) - 1] = '\0';
}
/*
int
	openquote(char *s, t_parsedata *pd)
{
	if (!pd->qt && isquote(s[pd->i]))
	{
		pd->qt = s[pd->i];
		collapsestr(s, pd->i);
		return (1);
	}
	return (0);
}

int
	closequote(char *s, t_parsedata *pd, t_list **r)
{
	if (pd->qt && s[pd->i] == pd->qt)
	{
		pd->qt = 0;
		collapsestr(s, pd->i);
		if (!s[pd->i] && pd->l == 1)
			addnulltoken(r);
		return (1);
	}
	return (0);
}
*/
