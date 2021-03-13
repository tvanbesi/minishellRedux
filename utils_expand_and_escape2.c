/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand_and_escape2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 18:09:41 by user42            #+#    #+#             */
/*   Updated: 2021/03/13 10:45:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	parse_expansion(t_list **atoken, char *buf, char *param, t_parsedata *pd)
{
	int	i;

	i = 0;
	while (param[i])
	{
		if (!pd->qt && ft_isspht(param[i]))
		{
			if (addtokenexpanded(atoken, buf) == -1)
				return (-1);
			while (ft_isspht(param[i]))
				i++;
			ft_bzero(buf, pd->idlen + 1);
			pd->j = 0;
		}
		else
			buf[pd->j++] = param[i++];
	}
	return (0);
}

int
	expand(t_list **atoken, char *src, t_parsedata *pd, t_list *env)
{
	if (src[pd->i + 1] == '?')
	{
		if (!(pd->param = ft_itoa(g_var.g_exitstatus)))
			return (-1);
		pd->j += ft_strlcat(pd->buf, pd->param, pd->idlen + 1);
		free(pd->param);
		pd->i += 2;
	}
	else if (ft_isalpha(src[pd->i + 1]) || src[pd->i + 1] == '_')
	{
		if ((pd->param = getidentifier(&src[pd->i + 1], env)))
			if (parse_expansion(atoken, pd->buf, pd->param, pd) == -1)
				return (-1);
		pd->i++;
		while (ft_isalnum(src[pd->i]) || src[pd->i] == '_')
			pd->i++;
	}
	else if (isquote(src[pd->i + 1]))
		pd->i++;
	else if (ft_isdigit(src[pd->i + 1]))
		pd->i += 2;
	else
		pd->buf[pd->j++] = src[pd->i++];
	return (0);
}
