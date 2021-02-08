/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 16:25:49 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/02/08 12:00:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	isquote(int c)
{
	return (c == 34 || c == 39);
}

int
	ismetachar(int c)
{
	return (c == ' ' || c == '\t' || c == ';'
		|| c == '<' || c == '>' || c == '|');
}

int
	isoperator(int c)
{
	return (c == ';' || c == '<' || c == '>' || c == '|');
}

int
	isspecialchar(int c)
{
	return (c == '$' || c == '\\' || isquote(c));
}

int
	emptytokenexception(char *word, t_list *env)
{
	int	i;

	i = 0;
	if (word[i++] != '$')
		return (0);
	if (!word[i])
		return (0);
	if (!(ft_isalpha(word[i]) || word[i] == '_'))
		return (0);
	while (word[++i])
	{
		if (!(ft_isalnum(word[i]) || word[i] == '_'))
			return (0);
	}
	if (findenv(env, &word[1]))
		return (0);
	return (1);
}
