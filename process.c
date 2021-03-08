/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:46:31 by tvanbesi          #+#    #+#             */
/*   Updated: 2021/03/08 21:12:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	handleexit(int stat_loc)
{
	if (WIFEXITED(stat_loc))
	{
		if (WEXITSTATUS(stat_loc) == -1)
			g_exitstatus = EXIT_STAT_FAIL;
		else
			g_exitstatus = WEXITSTATUS(stat_loc);
	}
	else if (WIFSIGNALED(stat_loc))
	{
		g_exitstatus = 128 + WTERMSIG(stat_loc);
		if (WTERMSIG(stat_loc) == SIGINT)
			write(STDERR, "\n", 1);
		else if (WTERMSIG(stat_loc) == SIGQUIT)
			write(STDERR, "Quit\n", 5);
	}
	return (0);
}

int
	process(t_list *command, t_shell *shell)
{
	int			stat_loc;
	char		*path;
	char		**argv;
	char		**envp;

	stat_loc = 0;
	if ((g_pid = fork()) == -1)
		return (-1);
	if (g_pid == 0)
	{
		path = getcmd(command);
		if (!(argv = getprocessargv(getcommandargv(command), path)))
			puterror(strerror(errno));
		else if (!(envp = getenvp(shell->env)))
			puterror(strerror(errno));
		else if (execve(path, argv, envp) == -1)
			puterror(strerror(errno));
		exit(-1);
	}
	else if (waitpid(g_pid, &stat_loc, 0) == -1)
		return (-1);
	g_pid = 0;
	return (handleexit(stat_loc));
}
