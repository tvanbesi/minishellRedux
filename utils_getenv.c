/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_getenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:29:01 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/02/08 14:31:59 by user42           ###   ########.fr       */
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
	l = ft_strlen(name) + ft_strlen(val) + 2;
	r = malloc(l);
	if (!r)
		return (NULL);
	ft_strlcpy(r, name, l);
	ft_strlcat(r, "=", l);
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
	envp = ft_calloc(envc + 1, sizeof(*envp));
	if (!envp)
		return (NULL);
	envp[envc] = NULL;
	current = env;
	i = 0;
	while (current)
	{
		envp[i] = getenvstr(current);
		if (!envp[i++])
		{
			ft_cafree(envp);
			return (NULL);
		}
		current = current->next;
	}
	return (envp);
}
