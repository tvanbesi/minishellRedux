/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 18:50:51 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/02 03:44:34 by user42           ###   ########.fr       */
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
	int	r;

	i = 0;
	r = 0;
	while (argv[i])
	{
		if (!isidentifiervalid(argv[i]) || ft_strchr(argv[i], '='))
		{
			if (argv[i][0] == '-' && i == 0)
			{
				puterror(ERROR_INVALID_OPTION);
				return (-2);
			}
			else
			{
				r = -1;
				puterror(ERROR_INVALID_IDENTIFIER);
			}
		}
		removeenv(aenv, argv[i++]);
	}
	return (r);
}
