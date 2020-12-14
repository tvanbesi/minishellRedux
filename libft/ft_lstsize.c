/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 19:10:26 by tvanbesi          #+#    #+#             */
/*   Updated: 2019/11/14 21:22:01 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int
	ft_lstsize(t_list *lst)
{
	int		n;
	t_list	*current;

	n = 0;
	current = lst;
	while (current)
	{
		n++;
		current = current->next;
	}
	return (n);
}
