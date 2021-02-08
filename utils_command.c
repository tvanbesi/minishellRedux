/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 10:34:27 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/02/08 12:23:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	assigncmd(t_list *token, t_list *command)
{
	t_list		*current;
	t_command	*commandcontent;

	commandcontent = command->content;
	current = token;
	while (current && gettokentype(current) == WORD)
	{
		if (gettokenstr(current))
		{
			commandcontent->cmd = gettokenstr(current);
			return ;
		}
		current = current->next;
	}
	commandcontent->cmd = NULL;
}

static int
	countargv(t_list *token)
{
	int		r;
	t_list	*current;

	r = 0;
	current = token;
	while (current)
	{
		if (gettokentype(current) == WORD && gettokenstr(current))
			r++;
		else if (gettokentype(current) == OPERATOR)
			return (r);
		current = current->next;
	}
	return (r);
}

int
	assignargv(t_list *token, t_list *command)
{
	char		**argv;
	int			argc;
	int			i;
	t_list		*current;
	t_command	*commandcontent;

	current = token;
	while (current && gettokentype(current) == WORD && !gettokenstr(current))
		current = current->next;
	if (current)
		current = current->next;
	argc = countargv(current);
	argv = ft_calloc(argc + 1, sizeof(*argv));
	if (!argv)
		return (-1);
	argv[argc] = NULL;
	i = 0;
	while (i < argc)
	{
		if (gettokentype(current) == WORD && gettokenstr(current))
			argv[i++] = gettokenstr(current);
		current = current->next;
	}
	commandcontent = command->content;
	commandcontent->argv = argv;
	return (0);
}
