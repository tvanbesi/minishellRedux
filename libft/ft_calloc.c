/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 09:32:18 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/02/08 17:00:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	b;

	b = count * size;
	if (!b)
		b = 1;
	p = malloc(b);
	if (!p)
		return (NULL);
	ft_bzero(p, b);
	return (p);
}
