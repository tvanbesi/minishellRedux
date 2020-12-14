/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_del.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 14:12:51 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/13 14:50:56 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	deltoken(void *p)
{
	t_token	*token;

	token = p;
	free(token->s);
}

void
	delcommand(void *p)
{
	t_command	*command;

	command = p;
	free(command->argv);
}

void
	delenv(void *p)
{
	t_env	*env;

	env = p;
	free(env->name);
	free(env->val);
}
