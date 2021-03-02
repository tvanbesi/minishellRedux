/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_getcommand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 18:15:49 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/02 17:37:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	getcommandtype(t_list *command)
{
	t_command	*content;

	content = command->content;
	return (content->type);
}

char
	*getcmd(t_list *command)
{
	t_command	*content;

	content = command->content;
	return (content->cmd);
}

char
	**getcommandargv(t_list *command)
{
	t_command	*content;

	content = command->content;
	return (content->argv);
}

t_list
	*getcommandredir(t_list *command)
{
	t_command	*content;

	content = command->content;
	return (content->redirections);
}

int
	getargc(char **argv)
{
	int	r;

	if (!argv)
		return (0);
	r = 0;
	while (*argv++)
		r++;
	return (r);
}
