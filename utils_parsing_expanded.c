/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_expanded.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 22:31:44 by user42            #+#    #+#             */
/*   Updated: 2021/03/10 22:03:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	addwordexpanded(t_list **r, char *input, t_parsedata *pd)
{
	if (addtokenexpanded(r, &input[pd->s], pd->l - 1, WORD) == -1)
		return (-1);
	pd->l = 0;
	while (ft_isspht(input[pd->i]))
		pd->i++;
	pd->s = pd->i;
	pd->l = 1;
	return (0);
}
