/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 08:39:15 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/14 10:33:51 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static char
	*detectidentifier(char *s, t_list *env)
{
	t_list	*current;
	size_t	idlen;
	size_t	i;
	
	idlen = 0;
	i = 0;
	if (ft_isalpha(s[i++]))
		idlen++;
	else
		return (NULL);
	while (ft_isalnum(s[i]) || s[i] == '_')
	{
		idlen++;
		i++;
	}
	current = env;
	while (current)
	{
		if (!ft_strncmp(getenvname(current), s, idlen))
			return (getenvval(current));
		current = current->next;
	}
	return (NULL);
}

static size_t
	getlen(char *s)
{
	size_t	r;
	size_t	i;

	r = 0;
	i = 0;
	while (s[i])
	{
		
		i++;
	}
	return (r);
}
*/
char
	*unquote(char *s)
{
	char	*r;
	char	*scpy;
	size_t	l;
	size_t	i;
	int		q;

	l = ft_strlen(s);
	if (!(r = malloc(l + 1)))
	{
		free(s);
		return (NULL);
	}
	q = 0;
	i = 0;
	scpy = s;
	while (*s)
	{
		if (!q && isquote(*s))
			q = *s;
		else if (q && q == *s)
			q = 0;
		else
		{
			r[i] = *s;
			i++;
		}
		s++;
	}
	r[i] = '\0';
	free(scpy);
	return (r);
}
