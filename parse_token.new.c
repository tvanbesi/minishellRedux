/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.new.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:41:23 by user42            #+#    #+#             */
/*   Updated: 2021/03/03 17:51:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char
	*getword(char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (ismetachar(input[i]))
			return (ft_substr(input, 0, i));
		i++;
	}
	return (ft_strdup(input));
}

t_list
	*parse_token(char *input)
{
	t_list	*r;
	int		i;

	if (!input)
		return (NULL);
	r = NULL;
	i = 0;
	while (input[i])
	{
		
		i++;
	}
	return (r);
}
