/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 12:56:58 by tvanbesi          #+#    #+#             */
/*   Updated: 2019/11/12 22:47:40 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int
	ft_isinset(char const *set, char c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char
	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	start = 0;
	while (*s1 && ft_isinset(set, *s1))
	{
		s1++;
		start++;
	}
	end = start;
	while (*s1)
	{
		s1++;
		end++;
	}
	while (end && ft_isinset(set, *--s1))
		end--;
	if (end)
		s1 -= end - 1;
	end = (end < start) ? start : end;
	return (ft_substr(s1, start, end - start));
}
