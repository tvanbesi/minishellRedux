/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:24:01 by tvanbesi          #+#    #+#             */
/*   Updated: 2019/11/15 19:35:10 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*cdst;
	const char	*csrc;

	if (!dst && !src)
		return (NULL);
	cdst = dst;
	csrc = src;
	while (n-- > 0)
		*cdst++ = *csrc++;
	return (dst);
}
