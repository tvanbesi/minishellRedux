/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:34:57 by user42            #+#    #+#             */
/*   Updated: 2021/03/02 17:36:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	isrediroperator(t_list *token)
{
	t_token	*content;

	content = token->content;
	if (!ft_strncmp(content->s, ">", 2)
	|| !ft_strncmp(content->s, "<", 2)
	|| !ft_strncmp(content->s, ">>", 3))
		return (1);
	return (0);
}

int
	ispipeorsemicolon(t_list *token)
{
	t_token	*content;

	content = token->content;
	if (!ft_strncmp(content->s, "|", 2) || !ft_strncmp(content->s, ";", 2))
		return (1);
	return (0);
}

int
	isvalidoperator(t_list *token)
{
	return (isrediroperator(token) || ispipeorsemicolon(token));
}
