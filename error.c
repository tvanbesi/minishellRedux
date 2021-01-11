/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 14:05:34 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/01/11 16:41:30 by user42           ###   ########.fr       */
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
