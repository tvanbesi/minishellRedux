/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_getenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:29:01 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/14 18:12:09 by tvanbesi         ###   ########.fr       */
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
	if (!(r = malloc(l)))
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
	if (!(envp = ft_calloc(envc + 1, sizeof(*envp))))
		return (NULL);
	envp[envc] = NULL;
	current = env;
	i = 0;
	while (current)
	{
		if (!(envp[i++] = getenvstr(current)))
		{
			ft_cafree(envp); //Is this actually safe ? Try
			return (NULL);
		}
		current = current->next;
	}
	return (envp);
}
