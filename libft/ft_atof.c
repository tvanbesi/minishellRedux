/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomasvanbesien <thomasvanbesien@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 14:29:53 by thomasvanbe       #+#    #+#             */
/*   Updated: 2020/08/22 15:42:36 by thomasvanbe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void
    mantissa(double *nb, char *str)
{
    int i;

    i = -1;
    while(ft_isdigit(*str))
        *nb += (double)(*str++ - '0') * ft_pow(10.0, i--);
}

double
    ft_atof(char *str)
{
    double  r;
    double  s;

    while(ft_isspace(*str))
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