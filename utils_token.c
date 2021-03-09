/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 16:25:49 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/09 02:09:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token
	*tokendup(void *p)
{
	t_token	*r;
	t_token	*content;

	if (!(r = malloc(sizeof(*r))))
		return (NULL);
	content = p;
	r->type = content->type;
	if (!(r->s = ft_strdup(content->s)))
	{
		free(r);
		return (NULL);
	}
	return (r);
}

int
	isquote(int c)
{
	return (c == '\'' || c == '\"');
}

int
	ismetachar(int c)
{
	return (c == ' ' || c == '\t' || isoperator(c));
}

int
	isoperator(int c)
{
	return (c == ';' || c == '<' || c == '>' || c == '|');
}

int
	isspecialchar(int c)
{
	return (c == '$' || c == '\\'); 
}
