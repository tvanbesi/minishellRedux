/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   emptytokenexception.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:38:35 by user42            #+#    #+#             */
/*   Updated: 2021/03/02 18:19:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	isemptytoken(char *s, t_list *env)
{
	int i;

	if (!s[1])
		return (0);
	i = 1;
	if (ft_isdigit(s[i]))
		return (1);
	if (!(ft_isalpha(s[i]) || s[i] == '_'))
		return (0);
	while (s[++i])
	{
		if (!(ft_isalnum(s[i]) || s[i] == '_'))
			return (0);
	}
	if (findenv(env, &s[1]))
		return (0);
	return (1);
}

int
	emptytokenexception(char *word, t_list *env)
{
	int	i;

	i = 0;
	if (word[i] != '$')
		return (0);
	while (word[i] == '$')
	{
		if (!isemptytoken(&word[i], env))
			return (0);
		if (ft_isdigit(word[++i]))
			i++;
		else
		{
			while (ft_isalnum(word[i]) || word[i] == '_')
				i++;
		}
	}
	if (word[i])
		return (0);
	return (1);
}
