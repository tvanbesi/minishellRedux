/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:30:55 by tvanbesi          #+#    #+#             */
/*   Updated: 2019/11/07 16:53:34 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned const char	*cs;
	unsigned char		uc;

	cs = s;
	uc = (unsigned char)c;
	while (n-- > 0)
	{
		if (*cs == uc)
			return (void*)cs;
		cs++;
	}
	return (NULL);
}
