/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_addtokenexpanded.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 22:00:35 by user42            #+#    #+#             */
/*   Updated: 2021/03/11 00:23:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	addnulltoken(t_list **atoken)
{
	t_list	*token;
	t_token	*content;
	char	*str;

	if (!(str = ft_strdup("")))
		return (-1);
	if (!(token = newtoken(WORD)))
	{
		free(str);
		return (-1);
	}
	content = token->content;
	content->s = str;
	ft_lstadd_back(atoken, token);
	return (0);
}

int
	addwordexpanded(t_list **r, char *input, t_parsedata *pd)
{
	if (addtokenexpanded(r, &input[pd->s], pd->l - 1, WORD) == -1)
		return (-1);
	pd->l = 0;
	while (ft_isspht(input[pd->i]))
		pd->i++;
	pd->s = pd->i;
	pd->l = 1;
	return (0);
}

int
	addtokenexpanded(t_list **atoken, const char *input, size_t l, int type)
{
	t_list	*token;
	t_token	*content;
	char	*str;

	if (l)
	{
		if (!(str = ft_substr(input, 0, l)))
			return (-1);
		if (!(token = newtoken(type)))
		{
			free(str);
			return (-1);
		}
		content = token->content;
		content->s = str;
		ft_lstadd_back(atoken, token);
	}
	return (0);
}
