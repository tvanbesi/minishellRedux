/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:27:54 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/09 15:57:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char
	*ft_strjoin(char const *s1, char const *s2)
{
	char	*r;
	size_t	n;

	n = ft_strlen(s1) + ft_strlen(s2);
	if (!(r = (char*)ft_calloc(n + 1, sizeof(char))))
		return (NULL);
	ft_strlcat(r, s1, n + 1);
	ft_strlcat(r, s2, n + 1);
	return (r);
}
