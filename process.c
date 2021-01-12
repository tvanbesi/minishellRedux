/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:46:31 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/01/11 19:44:51 by user42           ###   ########.fr       */
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

	if ((g_pid = fork()) == -1)
		return (-1);
	if (g_pid == 0)
	{
		if (!(argv = getprocessargv(getcommandargv(command), path)))
			exit(errno);
		else if (!(envp = getenvp(shell->env)))
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
