/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandcommand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 15:28:10 by user42            #+#    #+#             */
/*   Updated: 2021/03/10 20:04:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	expandcommand(t_list *command, t_list *env)
{
	t_list		*current;
	t_list		*expandedargv;
	t_command	*commandcontent;
	int			r;

	expandedargv = NULL;
	current = getcommandredir(command);
	if ((r = parse_redir(current, env)) < 0)
		return (r);
	current = getcommandargv(command);
	if (expandtoken(&expandedargv, current, env) == -1)
		return (-1);
	commandcontent = command->content;
	ft_lstclear(&commandcontent->argv, deltoken);
	commandcontent->argv = expandedargv;
	if (trimcommand(&commandcontent->argv) == -1)
		return (-1);
	return (0);
}
