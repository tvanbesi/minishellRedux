/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 08:45:23 by user42            #+#    #+#             */
/*   Updated: 2021/03/01 08:46:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	getredirtype(t_list *redir)
{
	t_redir	*content;

	content = redir->content;
	return (content->type);
}

char
	*getredirstr(t_list *redir)
{
	t_redir	*content;

	content = redir->content;
	return (content->fd_str);
}
