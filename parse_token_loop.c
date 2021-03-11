/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_loop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 20:38:14 by user42            #+#    #+#             */
/*   Updated: 2021/03/11 20:45:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	quote(int *qt, int c)
{
	if (!*qt && isquote(c))
		*qt = c;
	else if (*qt && *qt == c)
		*qt = 0;
}

static int
	escape(char *input, t_parsedata *pd)
{
	if (!input[pd->i + 1])
		return (-1);
	pd->i += 2;
	pd->l += 2;
	return (0);
}

static void
	inc(t_parsedata *pd)
{
	pd->i++;
	pd->l++;
}

int
	parse_token_loop(t_list **r, char *input, t_parsedata *pd)
{
	quote(&pd->qt, input[pd->i]);
	if (input[pd->i] == '\\')
	{
		if (escape(input, pd) == -1)
			return (-2);
	}
	else if (!pd->qt && ismetachar(input[pd->i]))
	{
		if (addword(r, input, pd) == -1)
			return (-1);
	}
	else
		inc(pd);
	return (0);
}
