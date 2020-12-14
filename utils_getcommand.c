/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_getcommand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 18:15:49 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/14 18:10:36 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	*getcmd(t_list *command)
{
	t_command	*content;

	content = command->content;
	return (content->cmd);
}

char
	**getcommandargv(t_list *command)
{
	t_command	*content;

	content = command->content;
	return (content->argv);
}

static int
	getargc(char **argv)
{
	int	r;

	if (!argv)
		return (0);
	r = 0;
	while (*argv++)
		r++;
	return (r);
}
		

char
	**getprocessargv(char **argv, char *path)
{
	char	**r;
	int		l;
	int		i;

	l = getargc(argv);
	if (!(r = ft_calloc(l + 2, sizeof(*r))))
		return (NULL);
	r[0] = ft_strrchr(path, '/');
	r[l + 1] = NULL;
	i = 0;
	while (argv[i])
	{
		r[i + 1] = argv[i];
		i++;
	}
	return (r);
}
