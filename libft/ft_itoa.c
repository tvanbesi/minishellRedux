/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 18:33:24 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/02/08 17:06:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t
	ft_itoas(int n)
{
	size_t	r;

	if (!n)
		return (1);
	r = 0;
	if (n < 0)
		r = 1;
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
	r = (char*)malloc(sizeof(*r) * (s + 1));
	if (!r)
		return (NULL);
	if (n < 0)
		*r++ = '-';
	i = s;
	if (n < 0)
		i--;
	while (i-- > 0)
	{
		if (n < 0)
			*r = (n / ft_p10(i)) * -1 + '0';
		else
			*r = (n / ft_p10(i)) + '0';
		r++;
		n %= ft_p10(i);
	}
	*r = '\0';
	return (r - s);
}
