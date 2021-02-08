/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:46:31 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/02/08 14:07:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	handleexit(int stat_loc)
{
	if (WIFEXITED(stat_loc))
	{
		if (WEXITSTATUS(stat_loc) > 1)
		{
			errno = WEXITSTATUS(stat_loc);
			return (-1);
		}
	}
	else if (WIFSIGNALED(stat_loc))
	{
		if (WTERMSIG(stat_loc) == SIGINT)
			write(STDOUT, "\n", 1);
		else if (WTERMSIG(stat_loc) == SIGQUIT)
			write(STDERR, "Quit\n", 5);
	}
	return (0);
}

int
	process(char *path, t_list *command, t_shell *shell)
{
	int			stat_loc;
	struct stat	buf;
	char		**argv;
	char		**envp;

	g_pid = fork();
	if (g_pid == -1)
		return (-1);
	if (g_pid == 0)
	{
		argv = getprocessargv(getcommandargv(command), path);
		if (!argv)
			exit(errno);
		envp = getenvp(shell->env);
		if (!envp)
			exit(errno);
		else if (execve(path, argv, envp) == -1)
			exit(errno);
	}
	else if (waitpid(g_pid, &stat_loc, 0) != g_pid)
		return (-1);
	setexitstatus(stat_loc);
	g_pid = 0;
	return (handleexit(stat_loc));
}
