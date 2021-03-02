/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 16:25:49 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/02 18:19:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	isquote(int c)
{
	return (c == 34 || c == 39);
}

int
	ismetachar(int c)
{
	return (c == ' ' || c == '\t' || c == ';'
	|| c == '<' || c == '>' || c == '|');
}

int
	isoperator(int c)
{
	return (c == ';' || c == '<' || c == '>' || c == '|');
}

int
	isspecialchar(int c)
{
	return (c == '$' || c == '\\' || isquote(c));
}
