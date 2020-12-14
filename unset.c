/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 18:50:51 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/13 19:28:45 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	removeenv(t_list **aenv, char *name)
{
	t_list	*current;
	t_list	*previous;

	current = *aenv;
	previous = NULL;
	while (current)
	{
		if (!ft_strncmp(getenvname(current), name, ft_strlen(name)))
		{
			if (previous)
				previous->next = current->next;
			else
				*aenv = current->next;
			ft_lstdelone(current, delenv);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

int
	unset(char **argv, t_list **aenv)
{
	int	i;

	if (!argv[0])
	{
		puterror(ERROR_NOT_ENOUGH_ARG);
		return (-2);
	}
	i = 0;
	while (argv[i])
		removeenv(aenv, argv[i++]);
	return (0);
}
