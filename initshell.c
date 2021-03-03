/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:01:08 by user42            #+#    #+#             */
/*   Updated: 2021/03/02 22:38:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	setshlvl(t_list **aenv)
{
	t_list	*env;
	char	*newenv;
	char	*newlvl;

	if ((env = findenv(*aenv, "SHLVL")))
	{
		if (!(newlvl = ft_itoa(ft_atoi(getenvval(env)) + 1)))
			return (-1);
		if (!(newenv = ft_strjoin("SHLVL=", newlvl)))
			return (-1);
		free(newlvl);
		if (addenv(aenv, newenv) == -1)
			return (-1);
	}
	else if (addenv(aenv, "SHLVL=1") == -1)
		return (-1);
	return (0);
}

static void
	initbuiltin(t_shell *shell)
{
	shell->b[0] = echo;
	shell->b[1] = cd;
	shell->b[2] = pwd;
	shell->b[3] = export;
	shell->b[4] = unset;
	shell->b[5] = env;
	shell->b[6] = exitshell;
}

t_shell
	*initshell(char **envp)
{
	t_shell	*shell;

	g_pid = 0;
	if (!(shell = malloc(sizeof(*shell))))
		return (NULL);
	if (envp)
		while (*envp)
			if (addenv(&shell->env, *envp++) == -1)
				return (NULL);
	if (setshlvl(&shell->env) == -1)
		return (NULL);
	shell->stdincpy = dup(STDIN);
	shell->stdoutcpy = dup(STDOUT);
	initbuiltin(shell);
	shell->exit = 0;
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
	return (shell);
}
