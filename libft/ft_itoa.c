/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 18:33:24 by tvanbesi          #+#    #+#             */
/*   Updated: 2019/11/13 15:21:52 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t
	ft_itoas(int n)
{
	size_t	r;

	if (!n)
		return (1);
	r = (n < 0) ? 1 : 0;
	while (n)
	{
		n /= 10;
		r++;
	}
	return (r);
}

static int
	ft_p10(size_t p)
{
	int	r;

	r = 1;
	while (p-- > 0)
		r *= 10;
	return (r);
}

char
	*ft_itoa(int n)
{
	size_t	s;
	size_t	i;
	char	*r;

	s = ft_itoas(n);
	if (!(r = (char*)malloc(sizeof(*r) * (s + 1))))
		return (NULL);
	if (n < 0)
		*r++ = '-';
	i = (n < 0) ? s - 1 : s;
	while (i-- > 0)
	{
		*r++ = (n < 0) ? (n / ft_p10(i)) * -1 + '0' : (n / ft_p10(i)) + '0';
		n %= ft_p10(i);
	}
	*r = '\0';
	return (r - s);
}
