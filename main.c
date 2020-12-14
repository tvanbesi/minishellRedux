/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 11:12:34 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/14 18:20:25 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char
	*prompt(void)
{
	char	*line;
	char	*r;
	int		gnl;

	r = NULL;
	while ((gnl = get_next_line(0, &line)) > 0)
	{
		r = ft_strdup(line);
		free(line);
	}
	free(line);
	return (r);
}

static t_shell
	initshell(void)
{
	t_shell	shell;

	shell.env = NULL;
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
		ft_putstr("> ");
		if (!(input = prompt()))
			puterror(strerror(errno));
		token = tokenize(input, shell.env);
		command = makecommands(token);
		execute(command, &shell);
		free(input);
		ft_lstclear(&token, deltoken);
		ft_lstclear(&command, delcommand);
	}
	ft_lstclear(&shell.env, delenv);
	return (0);
}
