/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 18:23:30 by tvanbesi          #+#    #+#             */
/*   Updated: 2019/11/15 13:27:55 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list
	*ft_lstnew(void *content)
{
	t_list	*r;

	if (!(r = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	r->content = content;
	r->next = NULL;
	return (r);
}
