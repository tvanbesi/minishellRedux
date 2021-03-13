/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 14:05:34 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/13 11:47:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	puterror(char *msg)
{
	write(STDERR, msg, ft_strlen(msg));
	write(STDERR, "\n", 1);
}

void
	*error(char *msg)
{
	puterror(msg);
	return (NULL);
}

void
	errorinvalidid(char *argv)
{
	ft_putstr_fd(ERROR_INVALID_IDENTIFIER, STDERR);
	ft_putstr_fd(" : \" ", STDERR);
	ft_putstr_fd(argv, STDERR);
	ft_putendl_fd(" \"", STDERR);
}
