/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_addtokenexpanded.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 22:00:35 by user42            #+#    #+#             */
/*   Updated: 2021/03/12 15:12:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	addnulltoken(t_list **atoken)
{
	t_list	*token;

	if (!(token = newtoken(WORD)))
		return (-1);
	ft_lstadd_back(atoken, token);
	return (0);
}

int
	addemptytoken(t_list **atoken)
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
	addtokenexpanded(t_list **atoken, const char *src)
{
	t_list	*token;
	t_token	*content;
	char	*str;

	if (!(str = ft_strdup(src)))
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
