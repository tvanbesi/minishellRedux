/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomasvanbesien <thomasvanbesien@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 14:39:18 by thomasvanbe       #+#    #+#             */
/*   Updated: 2020/08/22 15:17:29 by thomasvanbe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double
    ft_pow(double x, int y)
{
    double  r;

    if (x == 0.0)
        return (x);
    r = 1.0;
    if (y > 0)
        while (y-- > 0)
            r *= x;
    else
        while (y++ < 0)
            r /= x;
    return (r);
}