/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 11:12:34 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/16 09:34:12 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char
	*prompt(void)
{
	char	*line;
	int		gnl;

	while ((gnl = get_next_line(STDIN, &line)) != 1)
	{
		free(line);
		if (gnl == -1)
		{
			puterror(ERROR_GNL);
			return (NULL);
		}
	}
	return (line);
}

static t_shell
	initshell(void)
{
	t_shell	shell;

	shell.env = NULL;
	shell.stdincpy = dup(STDIN);
	shell.stdoutcpy = dup(STDOUT);
	return (shell);
}

int
	main(void)
{
	t_shell	shell;
	char	*input;
	t_list	*token;
	t_list	*command;

	shell = initshell();
	while (1)
	{
		write(STDOUT, "> ", 2);
		if (!(input = prompt()))
			puterror(strerror(errno));
		token = tokenize(input, shell.env);
		command = makecommands(token);
		cyclecommand(command, &shell);
		dup2(shell.stdincpy, STDIN);
		dup2(shell.stdoutcpy, STDOUT);
		free(input);
		ft_lstclear(&token, deltoken);
		ft_lstclear(&command, delcommand);
	}
	ft_lstclear(&shell.env, delenv);
	return (0);
}
