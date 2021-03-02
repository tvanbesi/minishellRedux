/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_getenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:29:01 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/01 23:47:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	*getenvname(t_list *env)
{
	t_env	*content;

	content = env->content;
	return (content->name);
}

char
	*getenvval(t_list *env)
{
	t_env	*content;

	content = env->content;
	return (content->val);
}

static char
	*getenvstr(t_list *env)
{
	char	*r;
	char	*name;
	char	*val;
	size_t	l;

	name = getenvname(env);
	val = getenvval(env);
	l = val ? ft_strlen(name) + ft_strlen(val) + 2 : ft_strlen(name) + 2;
	if (!(r = malloc(l)))
		return (NULL);
	ft_strlcpy(r, name, l);
	ft_strlcat(r, "=", l);
	if (val)
		ft_strlcat(r, val, l);
	return (r);
}

char
	**getenvp(t_list *env)
{
	char	**envp;
	int		envc;
	t_list	*current;
	int		i;

	envc = ft_lstsize(env);
	if (!(envp = ft_calloc(envc + 1, sizeof(*envp))))
		return (NULL);
	envp[envc] = NULL;
	current = env;
	i = 0;
	while (current)
	{
		if (!(envp[i++] = getenvstr(current)))
		{
			ft_cafree(envp);
			return (NULL);
		}
		current = current->next;
	}
	return (envp);
}
