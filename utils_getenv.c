/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_getenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:29:01 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/13 17:29:18 by tvanbesi         ###   ########.fr       */
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

