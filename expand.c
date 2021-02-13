/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 13:53:37 by user42            #+#    #+#             */
/*   Updated: 2021/02/13 14:34:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	expandone(char **s, t_list *env)
{
	if (emptytokenexception(*s, env))
	{
		free(*s);
		*s = NULL;
	}
	else if (!(*s = unquote(*s, env)))
		return (-1);
	return (0);
}

int
	expand(t_list *command, t_list *env)
{
	char	**argv;

	if (expandone(&((t_command*)command->content)->cmd, env) == -1)
		return (-1);
	argv = ((t_command*)command->content)->argv;
	if (argv)
		while (*argv)
			if (expandone(argv++, env) == -1)
				return (-1);
	return (0);
}
