/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:01:08 by user42            #+#    #+#             */
/*   Updated: 2021/03/13 10:41:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	setshlvl(t_list **aenv)
{
	t_list	*env;
	char	*newenv;
	char	*newlvl;

	newenv = NULL;
	if ((env = findenv(*aenv, "SHLVL")))
	{
		if ((newlvl = ft_itoa(ft_atoi(getenvval(env)) + 1)))
			newenv = ft_strjoin("SHLVL=", newlvl);
		free(newlvl);
		if (newenv)
			addenv(aenv, newenv);
		free(newenv);
		if (errno != 0)
		{
			puterror(strerror(errno));
			return (-1);
		}
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

static int
	initpwd(t_list **aenv)
{
	t_list	*env;
	char	*newenv;
	char	*cwd;

	newenv = NULL;
	if (!(env = findenv(*aenv, "PWD")) || !getenvval(env))
	{
		if (!(cwd = getcwd(NULL, 0)))
			return (-1);
		newenv = ft_strjoin("PWD=", cwd);
		if (newenv)
			addenv(aenv, newenv);
		free(newenv);
		if (errno != 0)
		{
			puterror(strerror(errno));
			return (-1);
		}
	}
	return (0);
}

t_shell
	*initshell(char **envp)
{
	t_shell	*shell;

	g_var.g_pid = 0;
	if (!(shell = malloc(sizeof(*shell))))
		return (NULL);
	shell->env = NULL;
	if (envp)
		while (*envp)
			if (addenv(&shell->env, *envp++) == -1)
				return (NULL);
	if (setshlvl(&shell->env) == -1)
		return (NULL);
	if (initpwd(&shell->env) == -1)
		return (NULL);
	shell->stdincpy = dup(STDIN);
	shell->stdoutcpy = dup(STDOUT);
	initbuiltin(shell);
	shell->exit = 0;
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
	return (shell);
}
