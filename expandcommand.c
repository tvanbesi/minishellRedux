/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandcommand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 15:28:10 by user42            #+#    #+#             */
/*   Updated: 2021/03/10 17:31:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	expandcommand(t_list *command, t_list *env)
{
	t_list		*current;
	t_token		*tokencontent;
	t_command	*commandcontent;
	int			r;

	current = getcommandredir(command);
	if ((r = parse_redir(current, env)) < 0)
		return (r);
	current = getcommandargv(command);
	while (current)
	{
		tokencontent = current->content;
		//expand token and add more inbetween if needed
		if ((r = expandtoken(tokencontent, env)) == -1)
			return (-1);
		current = current->next;
	}
	commandcontent = command->content;
	if (trimcommand(&commandcontent->argv) == -1)
		return (-1);
	return (0);
}
