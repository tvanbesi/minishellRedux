/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:53:34 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/02/08 17:27:25 by user42           ###   ########.fr       */
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
	tmp = ft_strchr(s, c);
	while (tmp)
	{
		ps = tmp;
		s = ps + 1;
		tmp = ft_strchr(s, c);
	}
	return ((char*)ps);
}
