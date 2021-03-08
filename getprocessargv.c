/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getprocessargv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:37:05 by user42            #+#    #+#             */
/*   Updated: 2021/03/08 21:13:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	**getprocessargv(t_list *argv, char *path)
{
	char	**r;
	int		l;
	int		i;

	argv = argv->next;
	l = ft_lstsize(argv);
	if (!(r = ft_calloc(l + 2, sizeof(*r))))
		return (NULL);
	r[0] = ft_strrchr(path, '/');
	r[l + 1] = NULL;
	i = 1;
	while (argv)
	{
		r[i] = gettokenstr(argv);
		argv = argv->next;
		i++;
	}
	return (r);
}
