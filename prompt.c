/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 14:15:05 by user42            #+#    #+#             */
/*   Updated: 2021/01/12 15:13:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	closefd(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

static int
	catchprompt(int stat_loc, int fd[2], char **line)
{
	int gnl;

	if (WEXITSTATUS(stat_loc) == ERROR)
	{
		g_exitstatus = EXIT_STAT_FAIL;
		return (-1);
	}
	else if (WEXITSTATUS(stat_loc) == BREAK)
	{
		g_exitstatus = 128 + SIGINT;
		if (!(*line = ft_strdup("")))
			return (-1);
		write(STDOUT, "\n", 1);
	}
	else if (WEXITSTATUS(stat_loc) == EXIT)
		exit(EXIT_STAT_SUCCESS);
	else if (WEXITSTATUS(stat_loc) == OK)
	{
		while ((gnl = get_next_line(fd[0], line)) != 1)
			if (gnl == -1)
				return (-1);
	}
	return (0);
}

static void
	lineflow(int fd[2], char *line)
{
	if (line)
		write(fd[1], line, ft_strlen(line));
	write(fd[1], "\n", 1);
	closefd(fd);
	if (line == NULL)
		exit(ERROR);
	else
		exit(OK);
}

int
	prompt(char **line)
{
	int		fd[2];
	int		stat_loc;

	if (pipe(fd) == -1)
		return (-1);
	if ((g_pid = fork()) == -1)
		return (-1);
	if (g_pid == 0)
	{
		*line = readstdin();
		lineflow(fd, *line);
	}
	else if (waitpid(g_pid, &stat_loc, 0) != g_pid)
		return (-1);
	g_pid = 0;
	if (WIFEXITED(stat_loc))
	{
		if (WEXITSTATUS(stat_loc) != OK)
			closefd(fd);
		if (catchprompt(stat_loc, fd, line) == -1)
			return (-1);
	}
	closefd(fd);
	return (0);
}
