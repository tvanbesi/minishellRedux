/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_commandsanity2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 12:25:32 by user42            #+#    #+#             */
/*   Updated: 2021/02/13 12:30:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	iserror(int n)
{
	return (n > ERROR_START && n < ERROR_END);
}

int
	isbuiltin(int n)
{
	return (n > BUILTIN_START && n < BUILTIN_END);
}
