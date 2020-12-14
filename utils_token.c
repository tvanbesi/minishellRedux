/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 16:25:49 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/14 08:56:49 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	isquote(int c)
{
	return (c == 34 || c == 39);
}

static t_list
	*newtoken(int type)
{
	t_list	*token;
	t_token	*content;

	if (!(content = malloc(sizeof(*content))))
		return (NULL);
	content->type = type;
	content->s = NULL;
	if (!(token = ft_lstnew(content)))
		free(content);
	return (token);
}

int
	addword(t_list **atoken, char *input, unsigned int i, size_t l)
{
	t_list	*token;
	t_token	*content;
	char	*s;

	if (l)
	{
		if (!(s = ft_substr(input, i - l, l)) || !(s = unquote(s)))
		{
			puterror(strerror(errno));
			return (-1);
		}
		if (!(token = newtoken(WORD)))
		{
			free(s);
			puterror(strerror(errno));
			return (-1);
		}
		content = token->content;
		content->s = s;
		ft_lstadd_back(atoken, token);
	}
	return (0);
}

int
	addmetachar(t_list **atoken, char *input, unsigned int i)
{
	t_list	*token;
	t_token	*content;
	char	*s;
	int		tokentype;

	if (!(s = ft_substr(input, i, 1)))
	{
		puterror(strerror(errno));
		return (-1);
	}
	tokentype = ft_isspht(input[i]) ? METACHARACTER : OPERATOR;
	if (!(token = newtoken(tokentype)))
	{
		free(s);
		puterror(strerror(errno));
		return (-1);
	}
	content = token->content;
	content->s = s;
	ft_lstadd_back(atoken, token);
	return (0);
}
