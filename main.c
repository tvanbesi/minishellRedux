/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 11:12:34 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/01/12 15:55:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_pid;
int		g_exitstatus;

static t_shell
	*initshell(char **envp)
{
	t_shell	*shell;

	if (!(shell = malloc(sizeof(*shell))))
		return (NULL);
	if (envp)
	{
		while (*envp)
			if (addenv(&shell->env, *envp++) == -1)
				return (NULL);
	}
	shell->stdincpy = dup(STDIN);
	shell->stdoutcpy = dup(STDOUT);
	shell->b[0] = echo;
	shell->b[1] = cd;
	shell->b[2] = pwd;
	shell->b[3] = export;
	shell->b[4] = unset;
	shell->b[5] = env;
	shell->b[6] = exitshell;
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
	return (shell);
}

void
	freedata(char *input, t_list *token, t_list *command)
{
	free(input);
	ft_lstclear(&token, deltoken);
	ft_lstclear(&command, delcommand);
}

int
	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	char	*input;
	t_list	*token;
	t_list	*command;

	if (!(shell = initshell(envp)))
	{
		puterror(strerror(errno));
		return (1);
	}
	g_pid = 0;
	while (1)
	{
		write(STDOUT, "> ", 2);
		if (prompt(&input) == -1)
			puterror(strerror(errno));
		dup2(shell->stdincpy, STDIN);
		dup2(shell->stdoutcpy, STDOUT);
		token = tokenize(input, shell->env);
		command = makecommands(token);
		cyclecommand(command, shell);
		freedata(input, token, command);
	}
	return (0);
}
