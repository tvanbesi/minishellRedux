/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:38:48 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/13 18:26:33 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	env(char **argv, t_list *env)
{
	t_list		*current;
	char		*name;
	char		*val;

	if (argv[0])
	{
		puterror(ERROR_TOO_MANY_ARG);
		return (-2);
	}
	current = env;
	while (current)
	{
		name = getenvname(current);
		val = getenvval(current);
		if (write(STDOUT, name, ft_strlen(name)) == -1)
			return (-1);
		if (write(STDOUT, "=", 1) == -1)
			return (-1);
		if (write(STDOUT, val, ft_strlen(val)) == -1)
			return (-1);
		if (write(STDOUT, "\n", 1) == -1)
			return (-1);
		current = current->next;
	}
	return (0);
}
