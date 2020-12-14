/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cafree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 11:55:08 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/13 10:12:37 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Frees a NULL-terminated array of char*.
*/

void
	ft_cafree(char **a)
{
	size_t	i;

	i = 0;
	if (!a)
		return ;
	while (a[i])
		free(a[i++]);
	free(a);
}
