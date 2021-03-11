/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redircmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 00:43:34 by user42            #+#    #+#             */
/*   Updated: 2021/03/11 01:04:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	ret(t_list **redir, t_token *tokencontent)
{
	ft_lstclear(redir, delredir);
	free(tokencontent->s);
	free(tokencontent);
	return (-1);
}

static void
	setpts(t_list **redir, t_token **tokencontent, t_list **newtoken)
{
	*redir = NULL;
	*tokencontent = NULL;
	*newtoken = NULL;
}

int
	parse_redircmd(t_list *token, t_list *command)
{
	t_list		*redir;
	t_command	*content;
	t_token		*tokencontent;
	t_list		*newtoken;

	content = command->content;
	while (token && !(gettokentype(token) == OPERATOR
	&& ispipeorsemicolon(token)))
	{
		if (gettokentype(token) == OPERATOR && isrediroperator(token))
		{
			setpts(&redir, &tokencontent, &newtoken);
			if (!(redir = newredir(gettokenstr(token))))
				return (ret(&redir, tokencontent));
			token = token->next;
			if (!(tokencontent = tokendup(token->content))
			|| !(newtoken = ft_lstnew(tokencontent)))
				return (ret(&redir, tokencontent));
			((t_redir*)redir->content)->fd_str = newtoken;
			ft_lstadd_back(&content->redirections, redir);
		}
		token = token->next;
	}
	return (0);
}
