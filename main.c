/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 11:12:34 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/22 11:23:44 by tvanbesi         ###   ########.fr       */
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
	return (shell);
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
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
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
		free(input);
		ft_lstclear(&token, deltoken);
		ft_lstclear(&command, delcommand);
	}
	ft_lstclear(&shell->env, delenv);
	free(shell);
	return (0);
}
