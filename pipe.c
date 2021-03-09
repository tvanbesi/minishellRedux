/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 12:09:27 by user42            #+#    #+#             */
/*   Updated: 2021/03/09 20:47:56 by user42           ###   ########.fr       */
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
	int	r;

	while (--n > 0)
		command = command->next;
	if ((r = expandcommand(command, shell->env)) < 0)
	{
		if (r == -1)
			puterror(strerror(errno));
	}
	else
		execute(command, shell);
}

static int
	getpipeexitstatus(int nchildren, int *pid_children)
{
	int	stat_loc;
	int	r;
	int	i;

	i = 0;
	r = 0;
	while (nchildren - i > 0)
	{
		if (waitpid(pid_children[i], &stat_loc, 0) == -1)
			return (-1);
		if (i == nchildren - 1)
			r = stat_loc;
		i++;
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
	int	*pid_children;
	int	r;

	nchildren = npipe + 1;
	if (!(pid_children = malloc(nchildren * sizeof(int))))
		return (-1);
	n = 0;
	while (n++ < nchildren)
	{
		if (n < nchildren && pipe(&fd[(n - 1) * 2]) == -1)
		{
			closefd(fd, n - 1);
			return (-1);
		}
		if ((pid = fork()) == -1)
			return (-1);
		if (pid == 0)
		{
			if (n > 1)
				dup2(fd[(n - 2) * 2], STDIN);
			if (n < nchildren)
				dup2(fd[(n - 1) * 2 + 1], STDOUT);
			closefd(fd, ft_min(n, npipe));
			pipecommand(command, shell, n);
			exit(g_exitstatus);
		}
		else
			pid_children[n - 1] = pid;
		if (n > 1)
		{
			close(fd[(n - 2) * 2]);
			close(fd[(n - 2) * 2 + 1]);
		}
	}
	r = getpipeexitstatus(nchildren, pid_children);
	free(pid_children);
	return (r);
}

int
	minipipe(t_list *command, t_shell *shell)
{
	int		*fd;
	int		stat_loc;
	int		npipe;

	stat_loc = 0;
	npipe = getnpipe(command);
	if (!(fd = (int*)malloc(sizeof(int) * npipe * 2)))
		return (-1);
	if ((g_exitstatus = minipipechildren(command, shell, fd, npipe)) == -1)
		puterror(strerror(errno));
	g_pid = 0;
	free(fd);
	return (0);
}
