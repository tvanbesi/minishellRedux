/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 22:31:44 by user42            #+#    #+#             */
/*   Updated: 2021/03/13 11:26:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	*errorparse(t_list **token, int c)
{
	ft_lstclear(token, deltoken);
	ft_putstr_fd(ERROR_PARSE, STDERR);
	ft_putstr_fd(" near unexpected symbol : ", STDERR);
	ft_putchar_fd(c, STDERR);
	write(STDERR, "\n", 1);
	g_var.g_exitstatus = EXIT_STAT_ERRORPARSE;
	return (NULL);
}

void
	*fail(t_list **token)
{
	ft_lstclear(token, deltoken);
	puterror(strerror(errno));
	g_var.g_exitstatus = EXIT_STAT_FAIL;
	return (NULL);
}

int
	addword(t_list **r, char *input, t_parsedata *pd)
{
	if (addtoken(r, &input[pd->s], pd->l - 1, WORD) == -1)
		return (-1);
	pd->l = 0;
	while (ismetachar(input[pd->i]))
	{
		while (ft_isspht(input[pd->i]))
			pd->i++;
		pd->s = pd->i;
		while (isoperator(input[pd->i]))
		{
			pd->i++;
			pd->l++;
		}
		if (addtoken(r, &input[pd->s], pd->l, OPERATOR) == -1)
			return (-1);
		while (ft_isspht(input[pd->i]))
			pd->i++;
		pd->s = pd->i;
		pd->l = 0;
	}
	pd->l = 1;
	return (0);
}
