/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 17:40:07 by user42            #+#    #+#             */
/*   Updated: 2021/03/13 11:27:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	initparsedata(t_parsedata *pd)
{
	pd->s = 0;
	pd->i = 0;
	pd->l = 1;
	pd->qt = 0;
}

static void
	*errorparsequote(t_list **r)
{
	ft_lstclear(r, deltoken);
	puterror(ERROR_PARSE_QUOTE);
	g_var.g_exitstatus = EXIT_STAT_ERRORPARSE;
	return (NULL);
}

static void
	*rett(t_list **r)
{
	ft_lstclear(r, deltoken);
	g_var.g_exitstatus = EXIT_STAT_ERRORPARSE;
	return (NULL);
}

t_list
	*parse_token(char *input)
{
	t_list			*r;
	int				ret;
	t_parsedata		pd;

	r = NULL;
	initparsedata(&pd);
	if (!input)
		return (NULL);
	while (input[pd.i])
		if ((ret = parse_token_loop(&r, input, &pd)) < 0)
		{
			if (ret == -1)
				return (fail(&r));
			return (errorparse(&r, input[pd.i]));
		}
	if (addtoken(&r, &input[pd.s], pd.l - 1, WORD) == -1)
		return (fail(&r));
	if (pd.qt)
		return (errorparsequote(&r));
	if (operatorsanity(r) == -1)
		return (rett(&r));
	return (r);
}
