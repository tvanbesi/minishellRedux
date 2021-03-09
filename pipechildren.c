/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipechildren.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 21:28:43 by user42            #+#    #+#             */
/*   Updated: 2021/03/09 23:25:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	ret(int *fd, int *pid_children, int n)
{
	free(pid_children);
	closefd(fd, n);
	return (-1);
}

static void
	pipeflow(int *fd, int n, int nchildren)
{
	if (n > 1)
		dup2(fd[(n - 2) * 2], STDIN);
	if (n < nchildren)
		dup2(fd[(n - 1) * 2 + 1], STDOUT);
	closefd(fd, ft_min(n, nchildren - 1));
}

static void
	close2fd(int n, int fd1, int fd2)
{
	if (n > 1)
	{
		close(fd1);
		close(fd2);
	}
}

int
	minipipechildren(t_list *command, t_shell *shell, int *fd, int npipe)
{
	int	nchildren;
	int	n;
	int	*pid_children;
	int	r;

	nchildren = npipe + 1;
	if (!(pid_children = malloc(nchildren * sizeof(int))))
		return (-1);
	n = 0;
	while (n++ < nchildren)
	{
		if ((n < nchildren && pipe(&fd[(n - 1) * 2]) == -1)
		|| ((g_pid = fork()) == -1))
			return (ret(fd, pid_children, n - 1));
		if ((pid_children[n - 1] = g_pid) == 0)
		{
			pipeflow(fd, n, nchildren);
			pipecommand(command, shell, n);
			exit(g_exitstatus);
		}
		close2fd(n, fd[(n - 2) * 2], fd[(n - 2) * 2 + 1]);
	}
	r = getpipeexitstatus(nchildren, pid_children);
	free(pid_children);
	return (r);
}
