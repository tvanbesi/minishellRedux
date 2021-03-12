/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandcommand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 15:28:10 by user42            #+#    #+#             */
/*   Updated: 2021/03/12 13:57:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	expandcommand(t_list *command, t_list *env)
{
	t_list		*tmp;
	t_list		*expandedargv;
	t_command	*commandcontent;
	int			r;

	expandedargv = NULL;
	tmp = getcommandredir(command);
	if ((r = parse_redir(tmp, env)) < 0)
		return (r);
	tmp = getcommandargv(command);
	if (expandtoken(&expandedargv, tmp, env) == -1)
		return (-1);
	commandcontent = command->content;
	ft_lstclear(&commandcontent->argv, deltoken);
	commandcontent->argv = expandedargv;
	if (trimcommand(&commandcontent->argv) == -1)
		return (-1);
	return (0);
}
