/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 15:48:01 by user42            #+#    #+#             */
/*   Updated: 2021/03/08 23:54:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	expansion(char *dst, char *src, t_list *env, int idlen)
{
	char	*strexitstatus;
	char	*param;

	if (src[1] == '?')
	{
		strexitstatus = ft_itoa(g_exitstatus);
		ft_strlcat(dst, strexitstatus, idlen + 1);
		free(strexitstatus);
	}
	else
	{
		if (!ft_isdigit(src[1])
		&& !(ft_isalpha(src[1]) || src[1] == '_'))
		{
			ft_strlcat(dst, "$", idlen + 1);
			return ;
		}
		if ((param = getidentifier(&src[1], env)))
			ft_strlcat(dst, param, idlen + 1);
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

int
	expandtoken(t_token *token, t_list *env)
{
	char	*s;
	size_t	idlen;
	int		i;
	int		j;
	int		qt;

	idlen = getidlen(token->s, env);
	if (!(s = ft_calloc(idlen + 1, sizeof(char))))
		return (-1);
	i = 0;
	j = 0;
	qt = 0;
	while (token->s[i])
	{
		if (!qt && isquote(token->s[i]))
			qt = token->s[i++];
		else if (qt && qt == token->s[i])
		{
			qt = 0;
			i++;
		}
		else if (qt != '\'' && token->s[i] == '\\')
		{
			s[j++] = token->s[++i];
			i++;
		}
		else if (qt != '\'' && token->s[i] == '$')
		{
			expansion(s, &(token->s[i]), env, idlen);
			i++;
			if (ft_isdigit(token->s[i]))
				i++;
			else if (token->s[i] == '?')
				i++;
			else
				while (ft_isalnum(token->s[i]) || token->s[i]  == '_')
					i++;
			if (!qt && !ft_strlen(s) && !token->s[i])
			{
				s = NULL;
				break ;
			}
			j = ft_strlen(s);
		}
		else
			s[j++] = token->s[i++];
	}
	free(token->s);
	token->s = s;
	if (!token->s)
		return (-2);
	return (0);
}

t_list
	*trimcommand(t_list **argv)
{
	t_list	*r;
	t_token	*content;
	t_list	*current;
	t_list	*tmp;

	current = *argv;
	r = NULL;
	while (current)
	{
		if (gettokenstr(current))
		{
			if (!(content = tokendup(current->content)))
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
		current = current->next;
	}
	return (r);
}

int
	expandcommand(t_list *command, t_list *env)
{
	t_list		*current;
	t_redir		*redircontent;
	t_token		*tokencontent;
	t_command	*commandcontent;
	int			r;

	current = getcommandredir(command);
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
	current = getcommandargv(command);
	while (current)
	{
		tokencontent = current->content;
		if ((r = expandtoken(tokencontent, env)) == -1)
			return (-1);
		current = current->next;
	}
	commandcontent = command->content;
	if (!(current = trimcommand(&commandcontent->argv)))
		return (-1);
	ft_lstclear(&commandcontent->argv, deltoken);
	commandcontent->argv = current;
	return (0);
}

