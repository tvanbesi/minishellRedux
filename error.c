/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 14:05:34 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/13 13:49:08 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	puterror(char *msg)
{
	write(STDERR, msg, ft_strlen(msg));
}

void
	*error(char *msg)
{
	puterror(msg);
	return (NULL);
}
