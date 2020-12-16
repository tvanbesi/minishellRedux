/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 11:12:34 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/16 18:00:02 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			if (shell->exit)
			{
				write(STDOUT, "exit", 4);
				exit(0);	//Should return correct exit status
			}
			else
				shell->exit = 1;
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
	shell->exit = 1;
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
	shell = initshell(envp);
	while (1)
	{
		write(STDOUT, "> ", 2);
		if (!(input = prompt(shell)))
			puterror(strerror(errno));
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
