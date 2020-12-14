/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 18:25:35 by tvanbesi          #+#    #+#             */
/*   Updated: 2019/11/07 17:20:46 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*cdst;
	const char	*csrc;

	cdst = dst;
	csrc = src;
	if (cdst < csrc)
		ft_memcpy(dst, src, len);
	else if (cdst > csrc)
		while (len-- > 0)
			*(cdst + len) = *(csrc + len);
	return (dst);
}
