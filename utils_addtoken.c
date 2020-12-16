/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_addtoken.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 07:27:17 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/16 19:08:32 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list
	*newtoken(int type)
{
	t_list	*token;
	t_token	*content;

	if (!(content = malloc(sizeof(*content))))
		return (NULL);
	content->type = type;
	content->s = NULL;
	if (!(token = ft_lstnew(content)))
		free(content);
	return (token);
}

int
	addword(t_list **atoken, const char *input, size_t l, t_list *env)
{
	t_list	*token;
	t_token	*content;
	char	*s;

	if (l)
	{
		if (!(s = ft_substr(input, 0, l)))
		{
			puterror(strerror(errno));
			return (-1);
		}
		if (emptytokenexception(s, env))
		{
			free(s);
			return (0);
		}
		if (!(s = unquote(s, env)))
		{
			puterror(strerror(errno));
			return (-1);
		}
		if (!(token = newtoken(WORD)))
		{
			free(s);
			puterror(strerror(errno));
			return (-1);
		}
		content = token->content;
		content->s = s;
		ft_lstadd_back(atoken, token);
	}
	return (0);
}

int
	addmetachar(t_list **atoken, const char *input)
{
	t_list			*token;
	t_token			*content;
	char			*s;
	unsigned int	i;
	size_t			l;
	
	i = 0;
	l = 0;
	while (ismetachar(input[i]))
	{
		if (ft_isspht(input[i]))
			i++;
		else if (isoperator(input[i]))
		{
			if (!(token = newtoken(OPERATOR)))
			{
				puterror(strerror(errno));
				return (-1);
			}
			while (isoperator(input[i]))
			{
				i++;
				l++;
			}
			if (!(s = ft_substr(input, i - l, l)))
			{
				puterror(strerror(errno));
				return (-1);
			}
			content = token->content;
			content->s = s;
			ft_lstadd_back(atoken, token);
			l = 0;
		}
	}
	return (0);
}
