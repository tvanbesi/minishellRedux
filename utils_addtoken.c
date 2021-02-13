/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_addtoken.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 07:27:17 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/02/13 15:40:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	addword(t_list **atoken, const char *input, size_t l)
{
	t_list	*token;
	t_token	*content;
	char	*s;

	if (l)
	{
		if (!(s = ft_substr(input, 0, l)))
			return (-1);
		if (!(token = newtoken(WORD)))
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
			if (!(token = newtoken(OPERATOR)))
				return (-1);
			while (isoperator(input[pd.i]))
				incrementparsedata(&pd);
			if (!(s = ft_substr(input, pd.i - pd.l, pd.l)))
				return (-1);
			((t_token*)token->content)->s = s;
			ft_lstadd_back(atoken, token);
			pd.l = 0;
		}
	}
	return (0);
}
