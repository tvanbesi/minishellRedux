/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 12:09:27 by user42            #+#    #+#             */
/*   Updated: 2021/02/13 14:50:33 by user42           ###   ########.fr       */
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
	exitstatpipe(int stat_loc)
{
	if (WEXITSTATUS(stat_loc) == NOCMD)
		g_exitstatus = EXIT_STAT_NOCMD;
	else if (WEXITSTATUS(stat_loc) == NOEXEC || WEXITSTATUS(stat_loc) == ISDIR)
		g_exitstatus = EXIT_STAT_NOEXEC;
	else if (!iserror(WEXITSTATUS(stat_loc)))
		g_exitstatus = EXIT_STAT_SUCCESS;
	else
		g_exitstatus = EXIT_STAT_FAIL;
}

static int
	minipiperecursion(t_list *command, t_shell *shell, int *fd, int npipe)
{
	static int	rlayer = 0;
	int			n;
	int			stat_loc;

	rlayer++;
	if (fork() == 0)
	{
		if (rlayer < npipe)
			minipiperecursion(command, shell, fd, npipe);
		if (rlayer == npipe)
		{
			dup2(fd[(rlayer - 1) * 2], STDIN);
			n = npipe;
			while (n-- > 0)
			{
				close(fd[(n * 2)]);
				close(fd[(n * 2) + 1]);
			}
			n = rlayer + 1;
			while (--n > 0)
				command = command->next;
			if (expand(command, shell->env) == -1)
				puterror(strerror(errno));
			if (getcommandtype(command) > REDIRECTION)
			{
				if (redirect(command, shell) == -1)
					puterror(strerror(errno));
				else
					execute(command, shell);
			}
			exit(0);
		}
	}
	else
	{
		if (rlayer > 1)
			dup2(fd[(rlayer - 2) * 2], STDIN);
		dup2(fd[(rlayer - 1) * 2 + 1], STDOUT);
		n = npipe;
		while (n-- > 0)
		{
			close(fd[(n * 2)]);
			close(fd[(n * 2) + 1]);
		}
		n = rlayer;
		while (--n > 0)
			command = command->next;
		if (expand(command, shell->env) == -1)
			puterror(strerror(errno));
		execute(command, shell);
		wait(&stat_loc);
		if (rlayer > 1)
			exit(0);
		//else
		//	exitstatpipe(stat_loc);
	}
	rlayer = 0;
	return (0);
}

int
	minipipe(t_list *command, t_shell *shell)
{
	int		*fd;
	int		stat_loc;
	int		npipe;
	int		n;

	npipe = getnpipe(command);
	if (!(fd = (int*)malloc(sizeof(int) * npipe * 2)))
		return (-1);
	n = 0;
	while (n++ < npipe)
		if (pipe(&fd[(n - 1) * 2]) == -1)
			return (-1);
	minipiperecursion(command, shell, fd, npipe);
	free(fd);
	fd = NULL;
	return (0);
}
