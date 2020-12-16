/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 13:29:19 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/16 10:50:00 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	showtoken(void *p)
{
	t_token	*token;

	token = p;
	if (token->type == WORD)
		printf("WORD\t\t");
	else if (token->type == OPERATOR)
		printf("OPERATOR\t");
	printf("|%s|\n", token->s);
}

void
	showcommand(void *p)
{
	t_command	*command;
	int			i;

	command = p;
	if (command->type == SIMPLE)
		printf("SIMPLE\t\t");
	else if (command->type == PIPE)
		printf("PIPE\t\t");
	else if (command->type == REDIRTRUNC)
		printf("REDIRTRUNC\t");
	else if (command->type == REDIRAPPEND)
		printf("REDIRAPPEND\t");
	else if (command->type == REDIRIN)
		printf("REDIRIN\t\t");
	else
		printf("TYPERROR\t");
	printf("CMD:|%s|\tARGV\t", command->cmd);
	i = 0;
	while (command->argv[i])
		printf("|%s| ", command->argv[i++]);
	printf("\n");
}

void
	showenv(void *p)
{
	t_env	*env;

	env = p;
	printf("|%s|=|%s|\n", env->name, env->val);
}
