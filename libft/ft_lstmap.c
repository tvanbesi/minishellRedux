/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 20:51:52 by tvanbesi          #+#    #+#             */
/*   Updated: 2019/11/14 17:14:55 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list
	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	**r;
	t_list	*current;
	t_list	*new;

	if (!lst)
		return (NULL);
	if (!(r = (t_list**)malloc(ft_lstsize(lst) * sizeof(*r))))
		return (NULL);
	*r = NULL;
	current = lst;
	while (current)
	{
		if (!(new = ft_lstnew(f(current->content))))
		{
			ft_lstclear(r, del);
			free(r);
			return (NULL);
		}
		ft_lstadd_back(r, new);
		current = current->next;
	}
	return (*r);
}
