/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 14:51:30 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/13 19:15:15 by tvanbesi         ###   ########.fr       */
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

int
	addenv(t_list **aenv, char *input)
{
	t_list	*env;
	t_env	*content;
	char	*name;
	char	*val;
	int		replace;

	if (!(val = ft_strchr(input, '=')))
		return (-2);
	if (!(val = ft_strdup(&val[1])))
		return (-1);
	if (!(name = ft_substr(input, 0, ft_strlen(input) - (ft_strlen(val) + 1))))
	{
		free(val);
		return (-1);
	}
	replace = 0;
	if ((env = findenv(*aenv, name)))
		replace = 1;
	else if (!(env = newenv()))
	{
		free(name);
		free(val);
		return (-1);
	}
	content = env->content;
	content->name = name;
	content->val = val;
	if (!replace)
		ft_lstadd_back(aenv, env);
	return (0);
}