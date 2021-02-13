/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 10:34:27 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/02/13 12:20:39 by user42           ###   ########.fr       */
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
			commandcontent->cmd = ft_strdup(gettokenstr(current));
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

static int
	tokentoargv(int i, int argc, t_list *current, char **argv)
{
	while (i < argc)
	{
		if (gettokentype(current) == WORD && gettokenstr(current))
			argv[i] = ft_strdup(gettokenstr(current));
		if (argv[i++] == NULL)
		{
			ft_cafree(argv);
			return (-1);
		}
		current = current->next;
	}
	return (0);
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
	current = current ? current->next : current;
	argc = countargv(current);
	if (!(argv = ft_calloc(argc + 1, sizeof(*argv))))
		return (-1);
	argv[argc] = NULL;
	i = 0;
	if (tokentoargv(i, argc, current, argv) == -1)
		return (-1);
	commandcontent = command->content;
	commandcontent->argv = argv;
	return (0);
}
