/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_getcommand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 18:15:49 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/08 19:39:33 by user42           ###   ########.fr       */
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
	t_list		*argv;
	t_token		*content;

	argv = getcommandargv(command);
	content = argv->content;
	return (content->s);
}

t_list
	*getcommandargv(t_list *command)
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
