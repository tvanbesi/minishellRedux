/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 11:12:34 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/02 17:07:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_pid;
int		g_exitstatus;

static void
	freedata(char **input, t_list **token, t_list **command)
{
	free(*input);
	*input = NULL;
	ft_lstclear(token, deltoken);
	ft_lstclear(command, delcommand);
}

static void
	miniloop(int argc, char **argv, t_shell *shell)
{
	int		quit;
	char	*input;
	t_list	*token;
	t_list	*command;

	quit = 0;
	while (!quit)
	{
		write(STDERR, "> ", 2);
		if ((quit = (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))))
			input = argv[2];
		else if (prompt(&input) == -1)
			puterror(strerror(errno));
		dup2(shell->stdincpy, STDIN);
		dup2(shell->stdoutcpy, STDOUT);
		token = tokenize(input);
		command = makecommands(token);
		cyclecommand(command, shell);
		freedata(&input, &token, &command);
	}
}

int
	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	if (!(shell = initshell(envp)))
	{
		puterror(strerror(errno));
		return (1);
	}
	miniloop(argc, argv, shell);
	return (0);
}
