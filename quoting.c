/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 08:39:15 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/15 11:06:10 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char
	*detectidentifier(char *s, t_list *env)
{
	t_list	*current;
	size_t	idlen;
	size_t	i;
	
	idlen = 0;
	i = 0;
	if (ft_isalpha(s[i]) || s[i] == '_')
		idlen++;
	else
		return (NULL);
	i++;
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
	getlen(char *s, t_list *env)
{
	size_t	r;
	size_t	i;
	char	*param;

	r = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			if ((param = detectidentifier(&s[i + 1], env)))
				r += ft_strlen(param);
			i++;
			while (ft_isalnum(s[i]) || s[i] == '_')
				i++;
		}
		else
		{
			r++;
			i++;
		}
	}
	return (r);
}

char
	*unquote(char *s, t_list *env)
{
	char	*r;
	size_t	l;
	size_t	i;
	size_t	j;
	int		q;
	char	*param;

	l = getlen(s, env);
	if (!(r = malloc(l + 1)))
	{
		free(s);
		return (NULL);
	}
	q = 0;
	i = 0;
	j = 0;
	while (s[j])
	{
		if (!q && isquote(s[j]))
		{
			q = s[j];
			j++;
		}
		else if (q && q == s[j])
		{
			q = 0;
			j++;
		}
		else
		{
			if (q != 34 && s[j] == '$')
			{
				if (!s[j + 1] || ft_isspht(s[j + 1]))
					r[i++] = s[j++]; //Remove token if token is only expanded unexisting param
				else if ((param = detectidentifier(&s[++j], env)))
					i += ft_strlcpy(&r[i], param, l + 1);
				while (ft_isalnum(s[j]) || s[j] == '_')
					j++;
			}
			else
				r[i++] = s[j++];
		}
	}
	r[i] = '\0';
	free(s);
	return (r);
}
