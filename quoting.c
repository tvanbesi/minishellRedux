/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 08:39:15 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/01 02:40:03 by user42           ###   ########.fr       */
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
	char	*strexitstatus;

	if (s[ud->j + 1] == '?')
	{
		strexitstatus = ft_itoa(g_exitstatus);
		ud->i += ft_strlcpy(&r[ud->i], strexitstatus, ud->l + 1);
		free(strexitstatus);
		ud->j += 2;
	}
	else
	{
		if (!ft_isdigit(s[ud->j + 1]) && !(ft_isalpha(s[ud->j + 1]) || s[ud->j + 1] == '_'))
			r[ud->i++] = s[ud->j++];
		else if ((ud->param = getidentifier(&s[++(ud->j)], env)))
			ud->i += ft_strlcpy(&r[ud->i], ud->param, ud->l + 1);
		if (ft_isdigit(s[ud->j]))
			ud->j++;
		else
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
		if (isspecialchar(s[ud->j + 1]))
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
	if (!(r = malloc(ud.l + 1)))
		free(s);
	while (s[ud.j])
	{
		if (!ud.q && isquote(s[ud.j]))
			editunquotedata(r, s, &ud, "open");
		else if (ud.q && ud.q == s[ud.j])
			editunquotedata(r, s, &ud, "close");
		else
		{
			if (ud.q != 39 && s[ud.j] == '\\')
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
