/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:06:58 by tvanbesi          #+#    #+#             */
/*   Updated: 2019/11/13 23:23:55 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char
	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*r;
	size_t	tmp;

	if (!(r = (char*)malloc(len + 1)))
		return (NULL);
	if (ft_strlen(s) > start)
	{
		tmp = ft_strlen(s + start);
		len = (len > tmp) ? tmp : len;
		ft_memcpy(r, s + start, len);
		r[len] = '\0';
	}
	else
		r[0] = '\0';
	return (r);
}
