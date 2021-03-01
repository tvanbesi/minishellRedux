/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_del.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 14:12:51 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/01 10:06:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	deltoken(void *p)
{
	t_token	*token;

	token = p;
	free(token->s);
	free(token);
}

void
	delcommand(void *p)
{
	t_command	*command;

	command = p;
	free(command->cmd);
	ft_cafree(command->argv);
	ft_lstclear(&command->redirections, delredir);
	free(command);
}

void
	delenv(void *p)
{
	t_env	*env;

	env = p;
	free(env->name);
	free(env->val);
	free(env);
}

void
	delredir(void *p)
{
	t_redir	*redir;

	redir = p;
	free(redir->fd_str);
	free(redir);
}
