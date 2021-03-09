/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:52:09 by user42            #+#    #+#             */
/*   Updated: 2021/03/09 16:02:30 by user42           ###   ########.fr       */
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
	expandtoken(t_token *token, t_list *env)
{
	char	*s;
	size_t	idlen;

	idlen = getidlen(token->s, env);
	if (!(s = ft_calloc(idlen + 1, sizeof(char))))
		return (-1);
	expand_and_escape(&s, token->s, idlen, env);
	free(token->s);
	token->s = s;
	if (!token->s)
		return (-2);
	return (0);
}

t_list
	*trimcommand(t_list *argv)
{
	t_list	*r;
	t_token	*content;
	t_list	*tmp;

	r = NULL;
	while (argv)
	{
		if (gettokenstr(argv))
		{
			if (!(content = tokendup(argv->content)))
			{
				ft_lstclear(&r, deltoken);
				return (NULL);
			}
			if (!(tmp = ft_lstnew(content)))
			{
				ft_lstclear(&r, deltoken);
				deltoken(content);
				return (NULL);
			}
			ft_lstadd_back(&r, tmp);
		}
		argv = argv->next;
	}
	return (r);
}

int
	parse_redir(t_list *current, t_list *env)
{
	int			r;
	t_redir		*redircontent;

	while (current)
	{
		redircontent = current->content;
		if ((r = expandtoken(redircontent->fd_str, env)) < 0)
		{
			if (r == -2)
				puterror(ERROR_BADREDIR);
			return (r);
		}
		current = current->next;
	}
	return (0);
}
