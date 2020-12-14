/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:53:34 by tvanbesi          #+#    #+#             */
/*   Updated: 2019/11/13 23:20:16 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char
	*ft_strrchr(const char *s, int c)
{
	const char	*ps;
	const char	*tmp;

	if (c == '\0')
		return (ft_strchr(s, c));
	ps = NULL;
	while ((tmp = ft_strchr(s, c)))
	{
		ps = tmp;
		s = ps + 1;
	}
	return ((char*)ps);
}
