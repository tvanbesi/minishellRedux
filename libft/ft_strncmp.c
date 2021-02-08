/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:18:50 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/02/08 17:22:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int
	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			tmp;

	tmp = n;
	if (n > ft_strlen(s1))
		n = ft_strlen(s1);
	if (n > ft_strlen(s2))
		n = ft_strlen(s2);
	if (n != tmp)
		n++;
	return (ft_memcmp(s1, s2, n));
}
