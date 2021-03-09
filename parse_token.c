/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 17:40:07 by user42            #+#    #+#             */
/*   Updated: 2021/03/09 15:33:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	*errorparse(t_list **token)
{
	ft_lstclear(token, deltoken);
	puterror(ERROR_PARSE);
	g_exitstatus = EXIT_STAT_ERRORPARSE;
	return (NULL);
}

static void
	*fail(t_list **token)
{
	ft_lstclear(token, deltoken);
	puterror(strerror(errno));
	g_exitstatus = EXIT_STAT_FAIL;
	return (NULL);
}

t_list
	*parse_token(char *input)
{
	t_list			*r;
	unsigned int	s;
	int				i;
	size_t			l;
	int				qt;

	r = NULL;
	s = 0;
	i = 0;
	l = 1;
	qt = 0;
	if (!input)
		return (NULL);
	while (input[i])
	{
		if (!qt && isquote(input[i]))
			qt = input[i];
		else if (qt && qt == input[i])
			qt = 0;
		if (input[i] == '\\')
		{
			if (!input[i + 1])
				return (errorparse(&r));
			i += 2;
			l += 2;
		}
		else if (!qt && ismetachar(input[i]))
		{
			if (addtoken(&r, input, s, l - 1, WORD) == -1)
				return (fail(&r));
			l = 0;
			while (ismetachar(input[i]))
			{
				while (ft_isspht(input[i]))
					i++;
				s = i;
				while (isoperator(input[i]))
				{
					i++;
					l++;
				}
				if (addtoken(&r, input, s, l, OPERATOR) == -1)
					return (fail(&r));
				while (ft_isspht(input[i]))
					i++;
				s = i;
				l = 0;
			}
			l = 1;
		}
		else
		{
			i++;
			l++;
		}
	}
	if (addtoken(&r, input, s, l - 1, WORD) == -1)
		return (fail(&r));
	if (operatorsanity(r) == -1)
		return (errorparse(&r));
	return (r);
}
