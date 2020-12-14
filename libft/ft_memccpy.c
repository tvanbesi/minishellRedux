/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:07:58 by tvanbesi          #+#    #+#             */
/*   Updated: 2019/11/07 17:19:52 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*cdst;
	unsigned const char	*csrc;
	unsigned char		uc;

	cdst = dst;
	csrc = src;
	uc = (unsigned char)c;
	while (n-- > 0)
	{
		*cdst++ = *csrc;
		if (*csrc++ == uc)
			return ((void*)cdst);
	}
	return (NULL);
}
