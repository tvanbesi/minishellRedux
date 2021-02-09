/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:25:11 by tvanbesi          #+#    #+#             */
/*   Updated: 2019/11/13 18:06:58 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t
	ft_wn(char const *s, char c)
{
	size_t	r;
	int		b;

	r = 0;
	b = 0;
	while (*s)
	{
		if (!b && *s != c)
		{
			r++;
			b = 1;
		}
		else if (b && *s == c)
			b = 0;
		s++;
	}
	return (r);
}

static void
	*ft_fr(char **r, size_t n)
{
	size_t	in;

	in = n;
	while (n-- > 0)
		free(*r++);
	free(r - in);
	return (NULL);
}

char
	**ft_split(char const *s, char c)
{
	char		**r;
	const char	*ps;
	size_t		cnt;
	size_t		start;
	size_t		end;

	cnt = ft_wn(s, c);
	if (!(r = (char**)ft_calloc(cnt + 1, sizeof(*r))))
		return (NULL);
	ps = s;
	start = 0;
	while (cnt-- > 0)
	{
		while (*ps++ == c)
			start++;
		end = start + 1;
		while (*ps && *ps++ != c)
			end++;
		if (!(*r = ft_substr(s, start, end - start)))
			return (ft_fr(r - (ft_wn(s, c) - (cnt + 1)), (ft_wn(s, c) - cnt)));
		r++;
		start = end + 1;
	}
	*r = NULL;
	return (r - ft_wn(s, c));
}
