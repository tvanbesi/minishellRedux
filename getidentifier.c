/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getidentifier.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:49:27 by user42            #+#    #+#             */
/*   Updated: 2021/03/09 14:59:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
