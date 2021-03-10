/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:52:09 by user42            #+#    #+#             */
/*   Updated: 2021/03/10 23:58:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	expansion(char *dst, char *src, t_list *env, t_parsedata *pd)
{
	char	*strexitstatus;
	char	*param;

	if (src[1] == '?')
	{
		strexitstatus = ft_itoa(g_exitstatus);
		ft_strlcat(dst, strexitstatus, pd->idlen + 1);
		free(strexitstatus);
	}
	else
	{
		if (!ft_isdigit(src[1])
		&& !(ft_isalpha(src[1]) || src[1] == '_')
		&& (!src[1] || src[1] == pd->qt || !isquote(src[1])))
			ft_strlcat(dst, "$", pd->idlen + 1);
		else if ((param = getidentifier(&src[1], env)))
			ft_strlcat(dst, param, pd->idlen + 1);
	}
}

int
	expandtoken(t_list **dst, t_list *src, t_list *env)
{
	t_list	*current;
	char	*rawargv;
	size_t	idlen;
	t_list	*tmp;

	current = src;
	while (current)
	{
		rawargv = NULL;
		idlen = getidlen(gettokenstr(current), env);
		if (!(rawargv = ft_calloc(idlen + 1, sizeof(char))))
			return (-1);
		expand_and_escape(&rawargv, gettokenstr(current), idlen, env);
		tmp = parse_token_expanded(rawargv);
		ft_lstadd_back(dst, tmp);
		free(rawargv);
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
	g_exitstatus = EXIT_STAT_FAIL;
}

int
	parse_redir(t_list *current, t_list *env)
{
	int		r;
	t_list	*expandedredir;
	t_redir	*redircontent;

	while (current)
	{
		expandedredir = NULL;
		redircontent = current->content;
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
		current = current->next;
	}
	return (0);
}
