/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 11:35:57 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/14 11:04:14 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	ismetachar(int c)
{
	return (c == ' ' || c == '\t' || c == ';' || c == '<' || c == '>' || c == '|');
}

static int
	quote(int qt, int c)
{
	if (!qt && isquote(c))
		qt = c;
	else if (qt && c == qt)
		qt = 0;
	return (qt);
}

t_list
	*tokenize(char *input, t_list *env)
{
	t_list			*r;
	unsigned int	i;
	size_t			l;
	int				qt;

	r = NULL;
	i = 0;
	l = 0;
	qt = 0;
	while (input[i])
	{
		l++;
		if (!(qt = quote(qt, input[i])) && ismetachar(input[i]))
		{
			l--;
			if (addword(&r, input, i, l, env) == -1)
				return (NULL);
			while (ismetachar(input[i]))
				if (addmetachar(&r, input, i++) == -1)
					return (NULL);
			l = 0;
		}
		else
			i++;
	}
	if (addword(&r, input, i, l, env) == -1)
		return (NULL);
	return (r);
}
