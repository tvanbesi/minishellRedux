/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 15:48:01 by user42            #+#    #+#             */
/*   Updated: 2021/03/09 14:43:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
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

char
	*getidentifier(char *s, t_list *env)
{
	t_list	*current;
	size_t	idlen;

	idlen = 0;
	if (ft_isalpha(s[0]) || s[0] == '_')
		idlen++;
	else
		return (NULL);
	while (ft_isalnum(s[idlen]) || s[idlen] == '_')
		idlen++;
	current = env;
	while (current)
	{
		if (!ft_strncmp(getenvname(current), s, idlen))
		{
			if (idlen == ft_strlen(getenvname(current)))
				return (getenvval(current));
			return (NULL);
		}
		current = current->next;
	}
	return (NULL);
}

static void
	escape(int *i, int *j, char *dst, char *src)
{
	(*i)++;
	dst[*j] = src[*i];
	(*j)++;
	(*i)++;
}

static int
	nulltoken(int qt, int l, char **s, int c)
{
	if (!qt && !l && !c)
	{
		free(*s);
		*s = NULL;
		return (1);
	}
	return (0);
}

static int
	quote(int *qt, int c, int *i)
{
	if (!*qt && isquote(c))
	{
		*qt = c;
		(*i)++;
		return (1);
	}
	else if (*qt && *qt == c)
	{
		*qt = 0;
		(*i)++;
		return (1);
	}
	return (0);
}

static void
	initpd(t_parsedata *pd, int idlen)
{
	pd->i = 0;
	pd->j = 0;
	pd->qt = 0;
	pd->idlen = idlen;
}

static void
	expand_and_escape(char **dst, char *src, int idlen, t_list *env)
{
	t_parsedata	pd;

	initpd(&pd, idlen);
	while (src[pd.i])
	{
		if (quote(&pd.qt, src[pd.i], &pd.i))
			;
		else if (shouldescape(src[pd.i], src[pd.i + 1], pd.qt))
			escape(&pd.i, &pd.j, *dst, src);
		else if (shouldexpand(src[pd.i], pd.qt))
		{
			expansion(*dst, &(src[pd.i++]), env, &pd);
			if (ft_isdigit(src[pd.i]) || src[pd.i] == '?')
				pd.i++;
			else
				while (ft_isalnum(src[pd.i]) || src[pd.i] == '_')
					pd.i++;
			if (nulltoken(pd.qt, ft_strlen(*dst), dst, src[pd.i]))
				return ;
			pd.j = ft_strlen(*dst);
		}
		else
			(*dst)[pd.j++] = src[pd.i++];
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

static t_list
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

static int
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
		if ((r = expandtoken(tokencontent, env)) == -1)
			return (-1);
		current = current->next;
	}
	commandcontent = command->content;
	if (!(current = trimcommand(commandcontent->argv)))
		return (-1);
	ft_lstclear(&commandcontent->argv, deltoken);
	commandcontent->argv = current;
	return (0);
}
