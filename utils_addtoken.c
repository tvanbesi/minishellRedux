/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_addtoken.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 07:27:17 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/02/08 12:29:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list
	*newtoken(int type)
{
	t_list	*token;
	t_token	*content;

	content = malloc(sizeof(*content));
	if (!content)
		return (NULL);
	content->type = type;
	content->s = NULL;
	token = ft_lstnew(content);
	if (!token)
		free(content);
	return (token);
}

int
	addword(t_list **atoken, const char *input, size_t l, t_list *env)
{
	t_list	*token;
	t_token	*content;
	char	*s;

	if (l)
	{
		s = ft_substr(input, 0, l);
		if (!s)
			return (-1);
		if (emptytokenexception(s, env))
		{
			free(s);
			s = NULL;
		}
		else
		{
			s = unquote(s, env);
			if (!s)
				return (-1);
		}
		token = newtoken(WORD);
		if (!token)
		{
			free(s);
			return (-1);
		}
		content = token->content;
		content->s = s;
		ft_lstadd_back(atoken, token);
	}
	return (0);
}

static void
	initparsedata(t_parsedata *pd)
{
	pd->i = 0;
	pd->l = 0;
}

static void
	incrementparsedata(t_parsedata *pd)
{
	pd->i++;
	pd->l++;
}

int
	addmetachar(t_list **atoken, const char *input)
{
	t_list			*token;
	char			*s;
	t_parsedata		pd;

	initparsedata(&pd);
	while (ismetachar(input[pd.i]))
	{
		if (ft_isspht(input[pd.i]))
			pd.i++;
		else if (isoperator(input[pd.i]))
		{
			token = newtoken(OPERATOR);
			if (!token)
				return (-1);
			while (isoperator(input[pd.i]))
				incrementparsedata(&pd);
			s = ft_substr(input, pd.i - pd.l, pd.l);
			if (!s)
				return (-1);
			((t_token*)token->content)->s = s;
			ft_lstadd_back(atoken, token);
			pd.l = 0;
		}
	}
	return (0);
}
