/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_getcommand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 18:15:49 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/13 18:20:57 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
