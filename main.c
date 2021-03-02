/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 11:12:34 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/02 07:06:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_pid;
int		g_exitstatus;

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
	else
		if (addenv(aenv, "SHLVL=1") == -1)
			return (-1);
	return (0);
}

static t_shell
	*initshell(char **envp)
{
	t_shell	*shell;

	g_pid = 0;
	if (!(shell = malloc(sizeof(*shell))))
		return (NULL);
	if (envp)
	{
		while (*envp)
			if (addenv(&shell->env, *envp++) == -1)
				return (NULL);
	}
	if (setshlvl(&shell->env) == -1)
		return (NULL);
	if (addenv(&shell->env, "_=/usr/bin/env") == -1)
		return (NULL);
	shell->stdincpy = dup(STDIN);
	shell->stdoutcpy = dup(STDOUT);
	shell->b[0] = echo;
	shell->b[1] = cd;
	shell->b[2] = pwd;
	shell->b[3] = export;
	shell->b[4] = unset;
	shell->b[5] = env;
	shell->b[6] = exitshell;
	shell->exit = 0;
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
	return (shell);
}

static void
	freedata(char **input, t_list **token, t_list **command)
{
	free(*input);
	*input = NULL;
	ft_lstclear(token, deltoken);
	ft_lstclear(command, delcommand);
}

int
	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	char	*input;
	t_list	*token;
	t_list	*command;
	int		quit;

	if (!(shell = initshell(envp)))
	{
		puterror(strerror(errno));
		return (1);
	}
	quit = 0;
	token = NULL;
	command = NULL;
	while (!quit)
	{
		write(STDERR, "> ", 2);
 		if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
		{
			input = argv[2];
			quit = 1;
		}
		else if (prompt(&input) == -1)
			puterror(strerror(errno));
		dup2(shell->stdincpy, STDIN);
		dup2(shell->stdoutcpy, STDOUT);
		token = tokenize(input);
		command = makecommands(token);
		cyclecommand(command, shell);
		freedata(&input, &token, &command);
	}
	return (0);
}

