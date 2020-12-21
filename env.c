/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:38:48 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/21 16:24:38 by tvanbesi         ###   ########.fr       */
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
		return (1);
	}
	current = env;
	while (current)
	{
		name = getenvname(current);
		val = getenvval(current);
		write(STDOUT, name, ft_strlen(name));
		write(STDOUT, "=", 1);
		write(STDOUT, val, ft_strlen(val));
		write(STDOUT, "\n", 1);
		current = current->next;
	}
	return (0);
}
