/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 10:45:13 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/02/08 17:19:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char
	*ft_strdup(const char *s1)
{
	size_t	s;
	char	*r;

	s = ft_strlen(s1);
	r = (char*)malloc(s + 1);
	if (!r)
		return (NULL);
	ft_strlcpy(r, s1, s + 1);
	return (r);
}
