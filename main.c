/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 11:12:34 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/22 09:29:27 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_skipeof;
pid_t	g_pid;
int		g_exitstatus;

static char
	*prompt(t_shell *shell)
{
	char	*line;
	int		gnl;

	while ((gnl = get_next_line(STDIN, &line)) != 1)
	{
		free(line);
		if (gnl == 0)
		{
			if (!g_skipeof)
			{
				write(STDOUT, "exit", 4);
				exit(EXIT_STAT_SUCESS);
			}
			else
				g_skipeof = 0;
		}
		if (gnl == -1)
		{
			puterror(ERROR_GNL);
			return (NULL);
		}
	}
	return (line);
}

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

	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
	if (!(shell = initshell(envp)))
	{
		puterror(strerror(errno));
		return (EXIT_STAT_FAIL);
	}
	g_skipeof = 0;
	g_pid = 0;
	g_exitstatus = EXIT_STAT_SUCESS;
	while (1)
	{
		write(STDOUT, "> ", 2);
		if (!(input = prompt(shell)))
			puterror(strerror(errno));
		token = tokenize(input, shell->env);
		command = makecommands(token);
		cyclecommand(command, shell);
		g_pid = 0;
		g_skipeof = 1;
		dup2(shell->stdincpy, STDIN);
		dup2(shell->stdoutcpy, STDOUT);
		free(input);
		ft_lstclear(&token, deltoken);
		ft_lstclear(&command, delcommand);
	}
	ft_lstclear(&shell->env, delenv);
	free(shell);
	return (0);
}
