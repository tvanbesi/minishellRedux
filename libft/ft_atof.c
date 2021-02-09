/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:07:19 by user42            #+#    #+#             */
/*   Updated: 2021/01/12 17:14:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void
	mantissa(double *nb, char *str)
{
	int	i;

	i = -1;
	while (ft_isdigit(*str))
		*nb += (double)(*str++ - '0') * ft_pow(10.0, i--);
}

double
	ft_atof(char *str)
{
	double	r;
	double	s;

	while (ft_isspace(*str))
		str++;
	s = 1.0;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			s = -1.0;
	r = 0.0;
	while (ft_isdigit(*str))
		r = r * 10.0 + (double)(*str++ - '0');
	if (*str != '.')
		return (r * s);
	mantissa(&r, ++str);
	return (r * s);
}
