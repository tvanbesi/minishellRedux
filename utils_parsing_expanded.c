/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_expanded.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 22:31:44 by user42            #+#    #+#             */
/*   Updated: 2021/03/12 17:00:48 by user42           ###   ########.fr       */
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
