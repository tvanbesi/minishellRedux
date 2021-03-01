/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 16:25:49 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/01 08:11:25 by user42           ###   ########.fr       */
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
	isrediroperator(t_list *token)
{
	t_token	*content;

	content = token->content;
	if (!ft_strncmp(content->s, ">", 2) || !ft_strncmp(content->s, "<", 2) || !ft_strncmp(content->s, ">>", 3))
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
