/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoull.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:10:14 by user42            #+#    #+#             */
/*   Updated: 2021/02/28 23:35:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long
	ft_atoll(const char *str)
{
	int			s;
	long long	r;

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
