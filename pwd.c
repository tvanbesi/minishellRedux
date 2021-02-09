/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 13:54:38 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/02/09 16:10:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	pwd(char **argv, t_list **aenv)
{
	char		*cwd;

	(void)aenv;
	(void)argv;
	if (!(cwd = getcwd(NULL, 0)))
		return (-1);
	write(STDOUT, cwd, ft_strlen(cwd));
	free(cwd);
	write(STDOUT, "\n", 1);
	return (0);
}
