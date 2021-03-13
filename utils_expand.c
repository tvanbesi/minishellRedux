/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:52:09 by user42            #+#    #+#             */
/*   Updated: 2021/03/13 10:45:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	canbeexpanded(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '?');
}

int
	expandtoken(t_list **dst, t_list *src, t_list *env)
{
	t_list	*current;
	t_list	*tmp;

	current = src;
	while (current)
	{
		if (!(tmp = expand_and_escape(gettokenstr(current), env)))
			return (-1);
		ft_lstadd_back(dst, tmp);
		current = current->next;
	}
	if (!*dst)
		return (-2);
	return (0);
}

static void
	badredir(void)
{
	puterror(ERROR_BADREDIR);
	g_var.g_exitstatus = EXIT_STAT_FAIL;
}

int
	parse_redir(t_list *redir, t_list *env)
{
	int		r;
	t_list	*expandedredir;
	t_redir	*redircontent;

	while (redir)
	{
		expandedredir = NULL;
		redircontent = redir->content;
		if ((r = expandtoken(&expandedredir, redircontent->fd_str, env)) < 0)
		{
			ft_lstclear(&expandedredir, deltoken);
			if (r == -2)
				badredir();
			return (r);
		}
		ft_lstclear(&redircontent->fd_str, deltoken);
		redircontent->fd_str = expandedredir;
		if (ft_lstsize(expandedredir) > 1)
		{
			badredir();
			return (-2);
		}
		redir = redir->next;
	}
	return (0);
}
