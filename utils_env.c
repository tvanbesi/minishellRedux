/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 14:51:30 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/02/08 15:34:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list
	*findenv(t_list *env, const char *name)
{
	t_list	*current;

	current = env;
	while (current)
	{
		if (!ft_strncmp(getenvname(current), name, ft_strlen(name)))
			return (current);
		current = current->next;
	}
	return (NULL);
}

static t_list
	*newenv(void)
{
	t_list	*env;
	t_env	*content;

	content = malloc(sizeof(*content));
	if (!content)
		return (NULL);
	content->name = NULL;
	content->val = NULL;
	env = ft_lstnew(content);
	if (!env)
	{
		ft_lstdelone(env, delenv);
		return (NULL);
	}
	return (env);
}

static int
	getenvdata(char *input, char **val, char **name)
{
	*val = ft_strchr(input, '=');
	if (!*val)
		return (-2);
	*val = ft_strdup(&(*val)[1]);
	if (!*val)
		return (-1);
	*name = ft_substr(input, 0, ft_strlen(input) - (ft_strlen(*val) + 1));
	if (!*name)
	{
		free(*val);
		return (-1);
	}
	return (0);
}

static t_list
	*sanenewenv(char *name, char *val)
{
	t_list	*env;

	env = newenv();
	if (!env)
	{
		free(name);
		free(val);
		return (NULL);
	}
	return (env);
}

int
	addenv(t_list **aenv, char *input)
{
	t_list	*env;
	char	*name;
	char	*val;
	int		replace;
	int		r;

	r = getenvdata(input, &val, &name);
	if (r < 0)
		return (r);
	replace = 0;
	env = findenv(*aenv, name);
	if (env)
		replace = 1;
	else
	{
		env = sanenewenv(name, val);
		if (!env)
			return (-1);
	}
	((t_env*)(env->content))->name = name;
	((t_env*)(env->content))->val = val;
	if (!replace)
		ft_lstadd_back(aenv, env);
	return (0);
}
