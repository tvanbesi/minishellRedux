/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 12:09:27 by user42            #+#    #+#             */
/*   Updated: 2021/02/27 14:46:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	getnpipe(t_list *command)
{
	int	r;

	r = 1;
	command = command->next;
	while (getcommandtype(command) == PIPE)
	{
		command = command->next;
		r++;
	}
	return (r);
}

static void
	pipecommand(t_list *command, t_shell *shell, int n)
{
	while (--n > 0)
		command = command->next;
	if (expand(command, shell->env) == -1)
		puterror(strerror(errno));
	execute(command, shell);
}

static int
	getpipeexitstatus(void)
{
	int	pid;
	int	stat_loc;
	int pidtmp;
	int	r;

	pidtmp = 0;
	while ((pid = wait(&stat_loc)) != -1)
	{
		if (pid > pidtmp)
			r = stat_loc;
		pidtmp = pid;
	}
	if (WIFEXITED(r))
		return (WEXITSTATUS(r));
	else if (WIFSIGNALED(r))
		return (WTERMSIG(r));
	else
		return (0);
}

static int
	minipipechildren(t_list *command, t_shell *shell, int *fd, int npipe)
{
	int	nchildren;
	int	n;
	int pid;

	nchildren = npipe + 1;
	n = 0;
	while (n++ < nchildren)
	{
		if ((pid = fork()) == -1)
			return (-1);
		if (pid == 0)
		{
			if (n != 1)
				dup2(fd[(n - 2) * 2], STDIN);
			if (n != nchildren)
				dup2(fd[(n - 1) * 2 + 1], STDOUT);
			closefd(fd, npipe);
			pipecommand(command, shell, n);
			exit(g_exitstatus);
		}
	}
	closefd(fd, npipe);
	return (getpipeexitstatus());
}

int
	minipipe(t_list *command, t_shell *shell)
{
	int		*fd;
	int		stat_loc;
	int		npipe;
	int		n;

	stat_loc = 0;
	npipe = getnpipe(command);
	if (!(fd = (int*)malloc(sizeof(int) * npipe * 2)))
		return (-1);
	n = 0;
	while (n++ < npipe)
		if (pipe(&fd[(n - 1) * 2]) == -1)
			return (-1);
	if ((g_exitstatus = minipipechildren(command, shell, fd, npipe)) == -1)
		puterror(strerror(errno));
	g_pid = 0;
	free(fd);
	fd = NULL;
	return (0);
}
