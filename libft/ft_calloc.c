/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 09:32:18 by tvanbesi          #+#    #+#             */
/*   Updated: 2019/11/12 20:06:19 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	b;

	b = count * size;
	b = b ? b : 1;
	if (!(p = malloc(b)))
		return (NULL);
	ft_bzero(p, b);
	return (p);
}
