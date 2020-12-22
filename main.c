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

static char
	*prompt(void)
{
	char	*line;
	char	buf[2];
	char	*tmp;
	int		lenfactor;
	size_t	len;
	size_t	r;

	if (!(line = malloc(BUFFER_SIZE)))
		return (NULL);
	lenfactor = 1;
	len = BUFFER_SIZE;
	ft_bzero(line, len);
	buf[1] = '\0';
	while ((r = read(STDIN, buf, 1)) > 0)
	{
		if (buf[0] == '\n')
			return (line);
		else if (ft_strlcat(line, buf, len) >= len)
		{
			lenfactor++;
			len = BUFFER_SIZE * lenfactor;
			tmp = line;
			if (!(line = malloc(len)))
			{
				free(tmp);
				return (NULL);
			}
			ft_bzero(line, len);
			ft_strlcpy(line, tmp, len);
			free(tmp);
		}
	}
	if (r == 0)
	{
		write(STDOUT, "exit", 4);
		exit(EXIT_STAT_SUCESS);
	}
	else
		return (NULL);
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
	g_pid = 0;
	g_exitstatus = EXIT_STAT_SUCESS;
	while (1)
	{
		write(STDOUT, "> ", 2);
		if (!(input = prompt()))
			puterror(strerror(errno));
		token = tokenize(input, shell->env);
		command = makecommands(token);
		cyclecommand(command, shell);
		g_pid = 0;
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
