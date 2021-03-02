/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 14:51:30 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/02 20:02:13 by user42           ###   ########.fr       */
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
		if (!ft_strncmp(getenvname(current), name, ft_strlen(name) + 1))
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

	if (!(content = malloc(sizeof(*content))))
		return (NULL);
	content->name = NULL;
	content->val = NULL;
	if (!(env = ft_lstnew(content)))
	{
		ft_lstdelone(env, delenv);
		return (NULL);
	}
	return (env);
}

static void
	freeforreplace(t_env *content)
{
	free(content->name);
	free(content->val);
}

int
	addenv(t_list **aenv, char *input)
{
	t_list	*env;
	char	*name;
	char	*val;
	int		replace;
	int		r;

	if ((r = getenvdata(input, &val, &name, aenv)) < 0)
		return (r);
	replace = 0;
	if ((env = findenv(*aenv, name)))
		replace = 1;
	else if (!(env = newenv()))
	{
		free(name);
		free(val);
		return (-1);
	}
	if (replace)
		freeforreplace(((t_env*)(env->content)));
	((t_env*)(env->content))->name = name;
	((t_env*)(env->content))->val = val;
	if (!replace)
		ft_lstadd_back(aenv, env);
	return (0);
}
