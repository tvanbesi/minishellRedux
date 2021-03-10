/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremovei.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 14:47:46 by user42            #+#    #+#             */
/*   Updated: 2021/03/10 14:59:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	ft_lstremovei(t_list **alst, void(*del)(void*), int i)
{
	t_list	*previous;
	t_list	*current;
	t_list	*next;

	if (!alst)
		return ;
	previous = NULL;
	current = *alst;
	while (current && i-- > 0)
	{
		previous = current;
		current = current->next;
	}
	if (!current)
		return ;
	next = current->next;
	if (!previous)
	{
		ft_lstdelone(current, del);
		*alst = next;
	}
	else
	{
		ft_lstdelone(current, del);
		previous->next = next;
	}
}
