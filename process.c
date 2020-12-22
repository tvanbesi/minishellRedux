/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:46:31 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/22 09:27:27 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	process(char *path, t_list *command, t_shell *shell)
{
	int				stat_loc;
	struct	stat	buf;
	char			**argv;
	char			**envp;

	if (stat(path, &buf) == -1)
		return (-1);
	if (buf.st_mode & S_IFDIR || !(buf.st_mode & S_IXUSR))
	{
		if (buf.st_mode & S_IFDIR)
			puterror(ERROR_ISDIR);
		else
			puterror(ERROR_ISNEXEC);
		g_exitstatus = EXIT_STAT_NOEXEC;
		return (0);
	}
	if ((g_pid = fork()) == -1)
		return (-1);
	if (g_pid == 0)
	{
		if (!(argv = getprocessargv(getcommandargv(command), path)))
			puterror(strerror(errno));
		else if (!(envp = getenvp(shell->env)))
			puterror(strerror(errno));
		else if (execve(path, argv, envp) == -1)
			puterror(strerror(errno));
		exit(1);
	}
	else if (waitpid(g_pid, &stat_loc, 0) != g_pid)
		return (-1);
	setexitstatus(stat_loc);
	g_pid = 0;
	dup2(shell->stdincpy, STDIN);
	dup2(shell->stdoutcpy, STDOUT);
	return (0);
}
