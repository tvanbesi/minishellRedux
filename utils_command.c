/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 10:34:27 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/13 18:20:52 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	assigncmd(t_list *token, t_list *command)
{
	t_token		*tokencontent;
	t_command	*commandcontent;

	tokencontent = token->content;
	commandcontent = command->content;
	commandcontent->cmd = tokencontent->s;
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
		if (gettokentype(current) == WORD)
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
	argc = countargv(current);
	if (!(argv = ft_calloc(sizeof(*argv), argc + 1)))
		return (-1);
	argv[argc] = NULL;
	i = 0;
	while (i < argc)
	{
		if (gettokentype(current) == WORD)
			argv[i++] = gettokenstr(current);
		current = current->next;
	}
	commandcontent = command->content;
	commandcontent->argv = argv;
	return (0);
}
