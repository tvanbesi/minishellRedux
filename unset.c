/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 18:50:51 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/13 11:46:57 by user42           ###   ########.fr       */
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

static int
	invalidoption(void)
{
	puterror(ERROR_INVALID_OPTION);
	return (-2);
}

int
	unset(t_list *argv, t_list **aenv)
{
	int		i;
	int		r;
	char	*arg;

	i = 0;
	r = 0;
	while (argv)
	{
		arg = gettokenstr(argv);
		if (!isidentifiervalid(arg) || ft_strchr(arg, '='))
		{
			if (arg[0] == '-' && i == 0)
				return (invalidoption());
			else
			{
				r = -3;
				errorinvalidid(arg);
			}
		}
		removeenv(aenv, arg);
		argv = argv->next;
	}
	return (r);
}
