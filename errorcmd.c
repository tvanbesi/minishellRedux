/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorcmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:37:25 by user42            #+#    #+#             */
/*   Updated: 2021/03/16 18:33:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	errornocmd(char *cmd)
{
	char	*errormsg;
	size_t	l;

	l = ft_strlen(ERROR_NOCMD) + 3 + ft_strlen(cmd) + 1;
	if (!(errormsg = ft_calloc(l + 1, sizeof(char))))
	{
		puterror(strerror(errno));
		return ;
	}
	ft_strlcpy(errormsg, ERROR_NOCMD, l + 1);
	ft_strlcat(errormsg, " : ", l + 1);
	ft_strlcat(errormsg, cmd, l + 1);
	ft_strlcat(errormsg, "\n", l + 1);
	write(STDERR, errormsg, l);
	free(errormsg);
}

static void
	errornoexec(char *cmd)
{
	char	*errormsg;
	size_t	l;

	l = ft_strlen(ERROR_ISNEXEC) + 3 + ft_strlen(cmd) + 1;
	if (!(errormsg = ft_calloc(l + 1, sizeof(char))))
	{
		puterror(strerror(errno));
		return ;
	}
	ft_strlcpy(errormsg, cmd, l + 1);
	ft_strlcat(errormsg, " : ", l + 1);
	ft_strlcat(errormsg, ERROR_ISNEXEC, l + 1);
	ft_strlcat(errormsg, "\n", l + 1);
	write(STDERR, errormsg, l);
	free(errormsg);
}

static void
	errornofile(char *cmd)
{
	char	*errormsg;
	size_t	l;

	l = ft_strlen(ERROR_NOFILE) + 3 + ft_strlen(cmd) + 1;
	if (!(errormsg = ft_calloc(l + 1, sizeof(char))))
	{
		puterror(strerror(errno));
		return ;
	}
	ft_strlcpy(errormsg, cmd, l + 1);
	ft_strlcat(errormsg, " : ", l + 1);
	ft_strlcat(errormsg, ERROR_NOFILE, l + 1);
	ft_strlcat(errormsg, "\n", l + 1);
	write(STDERR, errormsg, l);
	free(errormsg);
}

static void
	errorisdir(char *cmd)
{
	char	*errormsg;
	size_t	l;

	l = ft_strlen(ERROR_ISDIR) + 3 + ft_strlen(cmd) + 1;
	if (!(errormsg = ft_calloc(l + 1, sizeof(char))))
	{
		puterror(strerror(errno));
		return ;
	}
	ft_strlcpy(errormsg, cmd, l + 1);
	ft_strlcat(errormsg, " : ", l + 1);
	ft_strlcat(errormsg, ERROR_ISDIR, l + 1);
	ft_strlcat(errormsg, "\n", l + 1);
	write(STDERR, errormsg, l);
	free(errormsg);
}

void
	puterrorcmd(char *cmd, int n)
{
	if (n == NOCMD)
		errornocmd(cmd);
	else if (n == NOEXEC)
		errornoexec(cmd);
	else if (n == ISDIR)
		errorisdir(cmd);
	else if (n == NOFILE)
		errornofile(cmd);
}
