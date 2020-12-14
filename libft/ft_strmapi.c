/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 19:43:41 by tvanbesi          #+#    #+#             */
/*   Updated: 2019/11/07 18:04:21 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char
	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	size_t			l;
	char			*r;

	l = ft_strlen(s);
	if (!(r = (char*)malloc(l + 1)))
		return (NULL);
	i = 0;
	while (i < l)
		*r++ = f(i++, *s++);
	*r = '\0';
	return (r - l);
}
