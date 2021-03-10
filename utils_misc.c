/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_misc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 15:33:50 by user42            #+#    #+#             */
/*   Updated: 2021/03/10 16:11:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	skipidentifier(char *s, t_parsedata *pd)
{
	if (ft_isdigit(s[pd->i]) || s[pd->i] == '?')
		pd->i++;
	else
		while (ft_isalnum(s[pd->i]) || s[pd->i] == '_')
			pd->i++;
}
