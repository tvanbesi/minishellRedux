/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 15:05:20 by user42            #+#    #+#             */
/*   Updated: 2021/03/13 10:46:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_glob	g_var = {0, 0};

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
	input = NULL;
	while (!quit)
	{
		write(STDERR, "> ", 2);
		if ((quit = (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))))
		{
			if (!(input = ft_strdup(argv[2])))
				puterror(strerror(errno));
		}
		else if (prompt(&input) == -1)
			puterror(strerror(errno));
		dup2(shell->stdincpy, STDIN);
		dup2(shell->stdoutcpy, STDOUT);
		token = parse_token(input);
		command = parse_command(token);
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
