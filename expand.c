/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 13:53:37 by user42            #+#    #+#             */
/*   Updated: 2021/03/02 16:51:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	expandone(char **s, t_list *env)
{
	if (emptytokenexception(*s, env))
	{
		free(*s);
		*s = NULL;
	}
	else if (!(*s = unquote(*s, env)))
		return (-1);
	return (0);
}

static int
	expandredir(t_list *command, t_list *env)
{
	t_command	*commandcontent;
	t_list		*current;
	t_redir		*redircontent;

	commandcontent = command->content;
	current = commandcontent->redirections;
	while (current)
	{
		redircontent = current->content;
		if (expandone(&redircontent->fd_str, env) == -1)
			return (-1);
		current = current->next;
	}
	return (0);
}

static int
	expandargv(char **argv, t_list *env, char **expandedargv)
{
	int	i;

	i = 0;
	if (argv)
		while (*argv)
		{
			if (expandone(argv, env) == -1)
			{
				ft_cafree(expandedargv);
				return (-1);
			}
			if (*argv && !(expandedargv[i++] = ft_strdup(*argv)))
			{
				ft_cafree(expandedargv);
				return (-1);
			}
			argv++;
		}
	expandedargv[i] = NULL;
	return (0);
}

int
	expand(t_list *command, t_list *env)
{
	char	**expandedargv;
	char	**argv;
	int		argc;

	if (!getcmd(command))
		return (0);
	if (expandone(&((t_command*)command->content)->cmd, env) == -1)
		return (-1);
	argv = ((t_command*)command->content)->argv;
	argc = getargc(argv);
	if (!(expandedargv = ft_calloc(argc + 1, sizeof(char*))))
		return (-1);
	if (expandargv(argv, env, expandedargv) == -1)
		return (-1);
	argv = ((t_command*)command->content)->argv;
	ft_cafree(argv);
	((t_command*)command->content)->argv = expandedargv;
	if (expandredir(command, env) == -1)
		return (-1);
	return (0);
}
