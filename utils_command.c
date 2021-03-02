/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 10:34:27 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/02 19:53:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list
	*newcommand(int type)
{
	t_list		*command;
	t_command	*content;

	if (!(content = malloc(sizeof(*content))))
		return (NULL);
	content->type = type;
	content->cmd = NULL;
	content->argv = NULL;
	content->redirections = NULL;
	if (!(command = ft_lstnew(content)))
		free(content);
	return (command);
}

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
		if (gettokentype(current) == OPERATOR && isrediroperator(current))
			current = current->next;
		else if (gettokentype(current) == WORD && gettokenstr(current))
			r++;
		else if (gettokentype(current) == OPERATOR
		&& ispipeorsemicolon(current))
			return (r);
		current = current->next;
	}
	return (r);
}

static int
	tokentoargv(int argc, t_list *current, char **argv)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		if (gettokentype(current) == OPERATOR && isrediroperator(current))
			current = current->next;
		else
		{
			if (gettokentype(current) == WORD && gettokenstr(current))
				argv[i] = ft_strdup(gettokenstr(current));
			if (argv[i++] == NULL)
			{
				ft_cafree(argv);
				return (-1);
			}
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
	t_list		*current;
	t_command	*commandcontent;

	commandcontent = command->content;
	current = token;
	argc = countargv(current);
	if (!(argv = ft_calloc(argc + 1, sizeof(*argv))))
		return (-1);
	argv[argc] = NULL;
	if (tokentoargv(argc, current, argv) == -1)
		return (-1);
	commandcontent->argv = argv;
	return (0);
}
