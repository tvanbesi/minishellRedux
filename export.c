/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:52:33 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/02 18:20:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	isidentifiervalid(char *s)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(s[0]) || s[0] == '_'))
		return (0);
	i++;
	while (s[i] && s[i] != '=')
	{
		if (s[i] == '+' && s[i + 1] == '=')
			return (1);
		if (!(ft_isalnum(s[i]) || s[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static void
	showexport(t_list **aenv)
{
	t_list	*current;

	current = *aenv;
	while (current)
	{
		write(STDOUT, "declare -x ", 11);
		write(STDOUT, getenvname(current), ft_strlen(getenvname(current)));
		if (getenvval(current))
		{
			write(STDOUT, "=\"", 2);
			write(STDOUT, getenvval(current), ft_strlen(getenvval(current)));
			write(STDOUT, "\"", 1);
		}
		write(STDOUT, "\n", 1);
		current = current->next;
	}
}

static int
	handleinvalid(char *argv, int i)
{
	if (argv[0] == '-' && i == 0)
	{
		puterror(ERROR_INVALID_OPTION);
		return (-2);
	}
	else
	{
		puterror(ERROR_INVALID_IDENTIFIER);
		return (-1);
	}
}

int
	export(char **argv, t_list **aenv)
{
	int		i;
	int		r;

	if (!argv[0])
	{
		showexport(aenv);
		return (0);
	}
	i = 0;
	r = 0;
	while (argv[i])
	{
		if (!isidentifiervalid(argv[i]))
		{
			if ((r = handleinvalid(argv[i], i)) == -2)
				return (r);
		}
		else if (addenv(aenv, argv[i]) == -1)
			return (-1);
		i++;
	}
	return (r);
}
