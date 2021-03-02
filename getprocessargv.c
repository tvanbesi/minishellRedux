/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getprocessargv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:37:05 by user42            #+#    #+#             */
/*   Updated: 2021/03/02 17:37:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
