/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 14:51:30 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/02 00:21:43 by user42           ###   ########.fr       */
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

static int
	getenvdata(char *input, char **val, char **name, t_list **aenv)
{
	t_list	*env;
	char	*tmp;

	if (!(*val = ft_strchr(input, '=')))
	{
		*val = NULL;
		if (!(*name = ft_strdup(input)))
			return (-1);
	}
	else
	{
		if (*val - ft_strchr(input, '+') == 1)
		{
			if (!(*val = ft_strdup(&(*val)[1])))
				return (-1);
			if (!(*name = ft_substr(input, 0, ft_strlen(input) - (ft_strlen(*val) + 2))))
				return (-1);
			if ((env = findenv(*aenv, *name)) && getenvval(env))
			{
				tmp = *val;
				if (!(*val = ft_strjoin(getenvval(env), *val)))
					return (-1);
				free(tmp);
			}
		}
		else
		{
			if (!(*val = ft_strdup(&(*val)[1])))
				return (-1);
			if (!(*name = ft_substr(input, 0,
			ft_strlen(input) - (ft_strlen(*val) + 1))))
				return (-1);
		}
	}
	return (0);
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

	val = NULL;
	name = NULL;
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
