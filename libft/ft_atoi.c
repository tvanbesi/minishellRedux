/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomasvanbesien <thomasvanbesien@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:54:54 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/08/22 14:53:02 by thomasvanbe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int
	ft_atoi(const char *str)
{
	int s;
	int r;

	s = 1;
	r = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			s = -1;
	while (ft_isdigit(*str))
		r = r * 10 + (*str++ - '0');
	return (r * s);
}
