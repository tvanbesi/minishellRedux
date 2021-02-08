/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:06:58 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/02/08 17:25:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char
	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*r;
	size_t	tmp;

	r = (char*)malloc(len + 1);
	if (!r)
		return (NULL);
	if (ft_strlen(s) > start)
	{
		tmp = ft_strlen(s + start);
		if (len > tmp)
			len = tmp;
		ft_memcpy(r, s + start, len);
		r[len] = '\0';
	}
	else
		r[0] = '\0';
	return (r);
}
