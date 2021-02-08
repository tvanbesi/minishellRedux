/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 08:39:15 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/02/08 12:38:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	*getidentifier(char *s, t_list *env)
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

static void
	expansion(char *r, char *s, t_list *env, t_unquotedata *ud)
{
	if (s[ud->j + 1] == '?')
	{
		ud->i += ft_strlcpy(&r[ud->i], ft_itoa(g_exitstatus), ud->l + 1);
		ud->j += 2;
	}
	else
	{
		if (!s[ud->j + 1] || ft_isspht(s[ud->j + 1]))
			r[ud->i++] = s[ud->j++];
		else
		{
			ud->param = getidentifier(&s[++(ud->j)], env);
			if (ud->param)
				ud->i += ft_strlcpy(&r[ud->i], ud->param, ud->l + 1);
		}
		while (ft_isalnum(s[ud->j]) || s[ud->j] == '_')
			ud->j++;
	}
}

static void
	initunquotedata(char *s, t_list *env, t_unquotedata *ud)
{
	ud->l = getidlen(s, env);
	ud->q = 0;
	ud->i = 0;
	ud->j = 0;
}

static void
	editunquotedata(char *r, char *s, t_unquotedata *ud, char *mode)
{
	if (!ft_strncmp(mode, "open", 4))
	{
		ud->q = s[ud->j];
		ud->j++;
	}
	else if (!ft_strncmp(mode, "close", 5))
	{
		ud->q = 0;
		ud->j++;
	}
	else if (!ft_strncmp(mode, "special", 7))
	{
		r[ud->i++] = s[++(ud->j)];
		ud->j++;
	}
}

char
	*unquote(char *s, t_list *env)
{
	char			*r;
	t_unquotedata	ud;

	initunquotedata(s, env, &ud);
	r = malloc(ud.l + 1);
	if (!r)
		free(s);
	while (r && s[ud.j])
	{
		if (!ud.q && isquote(s[ud.j]))
			editunquotedata(r, s, &ud, "open");
		else if (ud.q && ud.q == s[ud.j])
			editunquotedata(r, s, &ud, "close");
		else
		{
			if (ud.q != 39 && s[ud.j] == '\\' && isspecialchar(s[ud.j + 1]))
				editunquotedata(r, s, &ud, "special");
			else if (ud.q != 39 && s[ud.j] == '$')
				expansion(r, s, env, &ud);
			else
				r[ud.i++] = s[ud.j++];
		}
	}
	r[ud.i] = '\0';
	free(s);
	return (r);
}
