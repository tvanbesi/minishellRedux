/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_addtoken.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 21:28:29 by user42            #+#    #+#             */
/*   Updated: 2021/03/08 22:43:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list
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
	addtoken(t_list **atoken, const char *input, unsigned int s, size_t l, int type)
{
	t_list	*token;
	t_token	*content;
	char	*str;
	char	*tmp;

	if (l)
	{
		if (!(str = ft_substr(input, s, l)))
			return (-1);
		if (!(token = newtoken(type)))
		{
			free(str);
			return (-1);
		}
		content = token->content;
		if (type == OPERATOR)
		{
			tmp = str;
			str = ft_strtrim(str, " \t");
			free(tmp);
			if (!str)
			{
				ft_lstdelone(token, deltoken);
				return (-1);
			}
		}
		content->s = str;
		if (ft_strlen(str))
			ft_lstadd_back(atoken, token);
		else
			ft_lstdelone(token, deltoken);
	}
	return (0);
}
