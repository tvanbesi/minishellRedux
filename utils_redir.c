/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 08:45:23 by user42            #+#    #+#             */
/*   Updated: 2021/03/10 17:53:11 by user42           ###   ########.fr       */
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

t_token
	*getredirtoken(t_list *redir)
{
	t_redir	*content;
	t_list	*fd_str;

	content = redir->content;
	fd_str = content->fd_str;
	return ((t_token*)fd_str->content);
}

char
	*getredirstr(t_list *redir)
{
	t_token	*token;

	token = getredirtoken(redir);
	return (token->s);
}

t_list
	*newredir(char *s)
{
	t_list		*redir;
	t_redir		*content;
	int			type;

	type = -1;
	if (!ft_strncmp(s, "<", 2))
		type = REDIRIN;
	else if (!ft_strncmp(s, ">", 2))
		type = REDIRTRUNC;
	else if (!ft_strncmp(s, ">>", 3))
		type = REDIRAPPEND;
	if (!(content = malloc(sizeof(*content))))
		return (NULL);
	content->type = type;
	content->fd_str = NULL;
	if (!(redir = ft_lstnew(content)))
		free(content);
	return (redir);
}
